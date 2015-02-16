#include "map.hpp"

#include <boost/algorithm/string.hpp>

#include "graphics/textures.hpp"
#include "utils/conversions.hpp"
#include "utils/files/file.hpp"
#include "utils/resources/game_config.hpp"

namespace graphics {

Map::Map(const std::string& map_filepath)
{
  // Read file
  std::string map_file_content;
  if( !utils::files::read(map_filepath, map_file_content) )
  {
    std::cerr << "Can't read map file: " << map_filepath << std::endl;
    throw;
  }

  // Split line by line
  std::vector<std::string> lines;
  boost::algorithm::split(lines, map_file_content, boost::is_any_of("\n"));

  // Currently read line
  size_t line_offset = 0;

  // Start interpreting the lines
  setTitle(lines.at( line_offset++ ));

  // Common container for line parts
  std::vector<std::string> parts;

  // Read starting positions
  boost::algorithm::split(parts, lines.at(line_offset++), boost::is_any_of(" "));
  m_tile_position.x = std::stoi( parts[0] );
  m_tile_position.y = std::stoi( parts[1] );

  // Init view
  m_view.setCenter(tileCenterPositionInPixel(m_tile_position));

  // Read sizes of the map
  boost::algorithm::split(parts, lines.at(line_offset++), boost::is_any_of(" "));
  size_t width  = std::stoi(parts.at(0));
  size_t height = std::stoi(parts.at(1));

  // Reserve map size
  m_tiles.resize(height);
  for( auto& row : m_tiles )
    row.resize(width);

  // Add tiles
  for( size_t y = 0; y < height; ++y )
  {
    for( size_t x = 0; x < width; ++x )
    {
      const std::string& line = lines.at(line_offset++);
      boost::algorithm::split(parts, line, boost::is_any_of(" "));

      auto& tile      = m_tiles[y][x];
      auto texture_id = std::stoi( parts[0] );
      auto& texture   = *Textures::get( texture_id );

      tile.sprite.setTexture( texture );
      tile.sprite.setScale(m_tile_size / texture.getSize().x,
                           m_tile_size / texture.getSize().y);
      tile.sprite.setPosition(x * m_tile_size, y * m_tile_size);
      tile.blocking = utils::conversions::boolean( parts[1] );
    }
  }
}

sf::Vector2f Map::tileCenterPositionInPixel(const utils::Position& tile_position) const
{
  static const float offset = m_tile_size / 2.f;
  return { tile_position.x * m_tile_size + offset, tile_position.y * m_tile_size + offset };
}

void Map::setTitle(const std::string& map_title)
{
  m_title = boost::trim_copy(map_title);
}

void Map::draw(sf::RenderTarget& target)
{
  target.setView(m_view);

  for( auto& row_of_tiles : m_tiles )
  {
    for( auto& tile : row_of_tiles )
      target.draw(tile.sprite);
  }

  smoothViewMoveToDestination();
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

  // Set new position
  m_tile_position.x = new_pos_x;
  m_tile_position.y = new_pos_y;
  m_movement_clock.restart();

  return true;
}

bool Map::canMoveTo(int x, int y) const
{
  if( y < 0 || (size_t)y >= m_tiles.size() )
    return false;

  const auto& row_of_tiles = m_tiles.at(y);
  if( x < 0 || (size_t)x >= row_of_tiles.size() )
    return false;

  return !row_of_tiles.at(x).blocking;
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
}

unsigned int Map::timeTakenToMove() const
{
  const static unsigned int time_taken = 1000.f / utils::GameConfig::mapMovementTilesPerSecond();
  return time_taken;
}

}
