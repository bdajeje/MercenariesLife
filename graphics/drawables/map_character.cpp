#include "map_character.hpp"

#include "utils/resources/game_config.hpp"

namespace graphics {

MapCharacter::MapCharacter(const sf::Texture& texture)
{
  m_sprite.setTexture(texture);

  // Resize sprite fo fit into a map tile
  const auto map_tile_size = utils::GameConfig::getMapTileSize();
  m_sprite.setScale( (float)map_tile_size / texture.getSize().x,
                     (float)map_tile_size / texture.getSize().y );
}

void MapCharacter::draw(sf::RenderTarget& target)
{
  target.draw(m_sprite);
}

}
