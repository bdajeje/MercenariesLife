#include "player.hpp"

#include "graphics/textures.hpp"

namespace models {

Player::Player(const std::string& info_filepath, sf::Vector2f position_on_screen)
  : Character {info_filepath}
  , MapCharacter {*graphics::Textures::get("characters/players/test.png")}
{
  setPosition( position_on_screen );
}

}
