#include "player.hpp"

#include "graphics/textures.hpp"

namespace models {

Player::Player(const std::string& info_filename, const sf::Vector2f& position, const sf::Vector2f& size)
  : Character {info_filename}
  , MapCharacter {info_filename, position, size, 4}
{

}

}
