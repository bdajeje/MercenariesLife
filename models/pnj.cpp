#include "pnj.hpp"

namespace models {

PNJ::PNJ(const std::string& filename, const sf::Vector2f& position, const sf::Vector2f size)
  : Character{filename}
  , graphics::MapCharacter{filename, position, size, 1}
{

}

}
