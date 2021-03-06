#include "map.hpp"

#include <boost/algorithm/string.hpp>

#include "events/talk_to_pnj.hpp"
#include "events/to_map.hpp"
#include "events/utils.hpp"
#include "graphics/textures.hpp"
#include "utils/conversions.hpp"
#include "utils/files/file.hpp"
#include "utils/rapidjson/document.h"
#include "utils/resources/game_config.hpp"

namespace graphics {

Map::Map(const std::string& map_name)
{
  const std::string map_filepath = "resources/maps/" + map_name;

  // Read file
  std::string map_file_content;
  if( !utils::files::read(map_filepath, map_file_content) )
  {
    std::cerr << "Can't read map file: " << map_filepath << std::endl;
    throw;
  }

  // Read json document
  rapidjson::Document document;
  document.Parse<0>(map_file_content.c_str());
  const auto& map = document["map"];

  // Read map info
  setMapName(map["name"].GetString());
  size_t width  = map["size"]["w"].GetInt();
  size_t height = map["size"]["h"].GetInt();

  // Create the map texture and sprite
  m_map_texture.loadFromFile(map_filepath + ".png");
  m_map_sprite.setTexture(m_map_texture);

  // Now load tiles
  m_tiles.resize(height);
  for( auto& row : m_tiles )
    row.resize(width);

  // Add tiles
  const auto& titles = map["tiles"];
  for( size_t y = 0; y < height; ++y )
  {
    for( size_t x = 0; x < width; ++x )
    {
      const auto& tile = titles[y*width + x];

      // Is blocking
      getTile(x, y).blocking = tile["blocking"].GetBool();

      // Read events
      const auto& events = tile["events"];
      for(rapidjson::SizeType offset = 0; offset < events.Size(); ++offset)
      {
         std::tuple<events::Type, events::Event*> event = events::createFromJSON(events[offset]);
         if(std::get<0>(event) == events::Type::None || !std::get<1>(event))
           continue;

         getTile(x, y).addEvent(std::get<0>(event), std::get<1>(event));
      }
    }
  }

  // Init view
  setPosition(map["start_pos"]["x"].GetInt(), map["start_pos"]["y"].GetInt());
  m_view.setCenter(tileCenterPositionInPixel(m_tile_position));

  // Load PNJs
  loadPNJs(map_filepath + ".pnj");
}

void Map::setPosition(int x, int y)
{
  if(!isValidPosition(x, y))
    return;

  m_tile_position.x = x;
  m_tile_position.y = y;
}

void Map::loadPNJs(const std::string& pnjs_filepath)
{
  // Read file
  std::string pnjs_file_content;
  if( !utils::files::read(pnjs_filepath, pnjs_file_content) )
  {
    std::cerr << "Can't read PNJs map file: " << pnjs_filepath << std::endl;
    throw;
  }

  // Split line by line
  std::vector<std::string> lines;
  boost::algorithm::split(lines, pnjs_file_content, boost::is_any_of("\n"));

  // Add PNJs
  const sf::Vector2f size {m_tile_size, m_tile_size};
  std::vector<std::string> parts;
  int x, y;
  for( const auto& line : lines )
  {
    // Get parts from line
    boost::algorithm::split(parts, line, boost::is_any_of(" "));

    // Ignore incorrect lines
    if(parts.size() != 3)
      continue;

    x = std::stoi(parts[0]);
    y = std::stoi(parts[1]);

    // Create PNJ and add it to a tile
    auto pnj = std::make_shared<models::PNJ>(parts[2], tileCornerPositionInPixel({x, y}), size);
    m_pnjs.push_back(pnj);
    getTile(x, y).pnj = pnj;
  }
}

sf::Vector2f Map::tileCenterPositionInPixel(const utils::Position& tile_position) const
{
  static const float offset = m_tile_size / 2.f;
  const auto corner_position = tileCornerPositionInPixel(tile_position);
  return { corner_position.x + offset, corner_position.y + offset };
}

sf::Vector2f Map::tileCornerPositionInPixel(const utils::Position& tile_position) const
{
  return { tile_position.x * m_tile_size, tile_position.y * m_tile_size };
}

void Map::setMapName(const std::string& map_title)
{
  m_map_name = boost::trim_copy(map_title);
}

void Map::draw(sf::RenderTarget& target, const sf::View& player_view)
{
  target.setView(m_view);

  // Draw map texture
  target.draw(m_map_sprite);

  // Draw PNJs
  for( auto& pnj : m_pnjs )
    pnj->draw(target);

  // Move the view if needed
  smoothViewMoveToDestination();

  // Draw player
  target.setView(player_view);
  m_player->draw(target);
}

bool Map::move(int x, int y)
{
  // Check last move call wasn't too close in time
  if( isMoving() )
    return false;

  // Check destination is reachabled
  const auto new_pos_x = m_tile_position.x + x;
  const auto new_pos_y = m_tile_position.y + y;
  if( !canMoveTo(new_pos_x, new_pos_y) )
    return false;

  // Leave previous tile events
  getCurrentTile().activate(events::Type::PlayerLeave);

  // Set new position
  setPosition(new_pos_x, new_pos_y);
  m_movement_clock.restart();

  // Go to new tile event
  getCurrentTile().activate(events::Type::PlayerTo);

  return true;
}

bool Map::isValidPosition(int x, int y) const
{
  // Out of Y bounds
  if( y < 0 || (size_t)y >= m_tiles.size() )
    return false;

  // Out of X bounds
  const auto& row_of_tiles = m_tiles.at(y);
  if( x < 0 || (size_t)x >= row_of_tiles.size() )
    return false;

  return true;
}

bool Map::canMoveTo(int x, int y) const
{
  if(!isValidPosition(x,y))
    return false;

  // PNJ on this tile (can't move onto a PNJ)
  const Tile& tile = getTile(x, y);
  if( tile.pnj )
    return false;

  return !tile.blocking;
}

bool Map::isMoving() const
{
  return tileCenterPositionInPixel(m_tile_position) != m_view.getCenter();
}

void Map::smoothViewMoveToDestination()
{
  // Not moving? Nothing to do
  if(!isMoving())
    return;

  // Calcul how many pixel we have to move depending on elapsed time
  const sf::Time elasped_time  = m_movement_clock.restart();
  const float tiles_per_second = utils::GameConfig::mapMovementTilesPerSecond();
  float distance_in_tiles      = elasped_time.asMilliseconds() * (tiles_per_second / 1000); // distance = speed * time
  float distance_in_pixels     = distance_in_tiles * m_tile_size;

  // Find which way to go
  const sf::Vector2f& view_position = m_view.getCenter();
  float x_move = 0;
  float y_move = 0;
  const sf::Vector2f view_movement_destination = tileCenterPositionInPixel(m_tile_position);
  if( view_position.x != view_movement_destination.x )
    x_move = (view_position.x < view_movement_destination.x) ? distance_in_pixels : -distance_in_pixels;
  if( view_position.y != view_movement_destination.y )
    y_move = (view_position.y < view_movement_destination.y) ? distance_in_pixels : -distance_in_pixels;

  // Finally move the view
  // If remaining distance is inferior to move_x simply directly position the view on target destination
  const float remaining_x_distance = std::abs(view_position.x - view_movement_destination.x);
  const float remaining_y_distance = std::abs(view_position.y - view_movement_destination.y);
  if( remaining_x_distance < x_move || remaining_y_distance < y_move )
    m_view.setCenter( view_movement_destination );
  else
    m_view.move( x_move, y_move );

  // Did we reach the destination?
  if( !isMoving() )
    moveDestinationReached();
}

void Map::moveDestinationReached()
{
  // Player reached destination, trigger destination possible events
  getCurrentTile().activate(events::Type::PlayerHere);
}

unsigned int Map::timeTakenToMove() const
{
  const static unsigned int time_taken = 1000.f / utils::GameConfig::mapMovementTilesPerSecond();
  return time_taken;
}

void Map::playerInteraction(utils::Direction direction)
{
  auto pnj = getPNJ(direction);
  if( pnj )
    events::Events::addEvent( new events::TalkToPNJ(pnj) );
}

std::shared_ptr<models::PNJ> Map::getPNJ(utils::Direction direction) const
{
  // Calculate which tile is targeted
  int x = m_tile_position.x;
  int y = m_tile_position.y;
  if( direction == utils::Direction::Left )
    x--;
  else if( direction == utils::Direction::Right )
    x++;
  if( direction == utils::Direction::Up )
    y--;
  else if( direction == utils::Direction::Down )
    y++;

  // Bounds verification
  if( !isValidPosition(x, y) )
    return nullptr;

  return getTile(x, y).pnj;
}

void Map::keyPress(sf::Keyboard::Key key_code)
{
  if(key_code == utils::GameConfig::keyboardKey( utils::KeyboardActions::MapPlayerInteraction ))
    playerInteraction( m_player->direction() );
}

void Map::keyboardAction()
{
  if( isMoving() )
    return;

  if(sf::Keyboard::isKeyPressed( utils::GameConfig::keyboardKey( utils::KeyboardActions::MapMoveUp ) ))
  {
    m_player->setDirection(utils::Direction::Up);

    if(move(0, -1))
      m_player->move( timeTakenToMove() );
  }
  else if(sf::Keyboard::isKeyPressed( utils::GameConfig::keyboardKey( utils::KeyboardActions::MapMoveDown ) ))
  {
    m_player->setDirection(utils::Direction::Down);

    if( move(0, 1) )
      m_player->move( timeTakenToMove() );
  }
  else if(sf::Keyboard::isKeyPressed( utils::GameConfig::keyboardKey( utils::KeyboardActions::MapMoveLeft ) ))
  {
    m_player->setDirection(utils::Direction::Left);

    if( move(-1, 0) )
      m_player->move( timeTakenToMove() );
  }
  else if(sf::Keyboard::isKeyPressed( utils::GameConfig::keyboardKey( utils::KeyboardActions::MapMoveRight ) ))
  {
    m_player->setDirection(utils::Direction::Right);

    if( move(1, 0) )
      m_player->move( timeTakenToMove() );
  }
}

}
