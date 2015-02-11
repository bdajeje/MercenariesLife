#include "map.hpp"

#include <boost/algorithm/string.hpp>

#include "graphics/textures.hpp"
#include "utils/files/file.hpp"
#include "utils/resources/game_config.hpp"

namespace graphics {

Map::Map(unsigned int window_width, unsigned int window_height, const std::string& map_filepath)
  : m_view( sf::Vector2f{window_width / 2.f, window_height / 2.f}, sf::Vector2f{(float)window_width, (float)window_height} )
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

  // Check minimum mandatory number of lines
  if( lines.size() < 3 )
  {
    std::cerr << "Wrong map file format (1)" << std::endl;
    throw;
  }

  // Start interpreting the lines
  setTitle(lines.at(0));

  // Read sizes of the map
  std::vector<std::string> map_sizes;
  boost::algorithm::split(map_sizes, lines.at(1), boost::is_any_of(" "));
  if(map_sizes.size() != 2)
  {
    std::cerr << "Wrong map file format (2)" << std::endl;
    throw;
  }
  size_t width  = std::stoi(map_sizes.at(0));
  size_t height = std::stoi(map_sizes.at(1));

  // Reserve map size
  m_tiles.resize(height);
  for( auto& row : m_tiles )
    row.resize(width);

  // Add tiles
  const auto tile_size = utils::GameConfig::getMapTileSize();
  const size_t tiles_start_pos = 2;
  for( size_t y = 0; y < height; ++y )
  {
    for( size_t x = 0; x < width; ++x )
    {
      auto& sprite  = m_tiles[y][x];
      auto texture_id = std::stoi( lines.at(y * width + x + tiles_start_pos) );
      auto& texture = *Textures::get( texture_id );

      sprite.setTexture( texture );
      sprite.setScale((float)tile_size / texture.getSize().x,
                      (float)tile_size / texture.getSize().y);
      sprite.setPosition(x * tile_size, y * tile_size);
    }
  }
}

void Map::setTitle(const std::string& map_title)
{
  m_title = boost::trim_copy(map_title);
}

void Map::draw(sf::RenderTarget& target)
{
  for( auto& row_of_sprites : m_tiles )
  {
    for( auto& sprite : row_of_sprites )
      target.draw(sprite);
  }
}

void Map::move(int x, int y)
{
  // Check last move call wasn't too close in time
  if( !isMovementAllowed() )
    return;

  // Move the view
  const int tile_size = utils::GameConfig::getMapTileSize();
  m_view.move( x * tile_size, y * tile_size );

  // Register last move time
  m_movement_clock.restart();
}

bool Map::isMovementAllowed() const
{
  // utils::GameConfig::getMapMovementSpeed() returns speed per seconds
  // So here we find one movement duration to test if last movement time isn't too current time
  const float movement_duration = 1000.0 / utils::GameConfig::getMapMovementSpeed();

  return m_movement_clock.getElapsedTime().asMilliseconds() >= movement_duration ? true : false;
}

}
