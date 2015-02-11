#ifndef MODELS_PLAYER_HPP
#define MODELS_PLAYER_HPP

#include "models/character.hpp"
#include "graphics/drawables/map_character.hpp"

namespace models {

class Player : public Character,
               public graphics::MapCharacter
{
  public:

    /*! Player constructor
     * \param info_filepath - where to find information about player
     * \param position_on_screen - position where to draw the player sprite
     */
    Player(const std::string& info_filepath, sf::Vector2f position_on_screen);
};

}

#endif // MODELS_PLAYER_HPP
