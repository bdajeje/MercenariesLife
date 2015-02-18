#include "pnj.hpp"

#include "graphics/textures.hpp"

namespace models {

PNJ::PNJ(const std::string& filename, const sf::Vector2f& position, const sf::Vector2f size)
  : Character{filename}
  , graphics::MapCharacter{filename, position, size, 1}
{

}

const sf::Texture& PNJ::getPortrait() const
{
  return *graphics::Textures::get( "characters/" + m_id + "/portrait.png" );
}

}
