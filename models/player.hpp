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
     * \param info_filename - where to find information about player
     * \param position      - position where to draw the player sprite
     * \param size          - size to scale player texture
     */
    Player(const std::string& info_filename, const sf::Vector2f& position, const sf::Vector2f& size);
};

}

#endif // MODELS_PLAYER_HPP
