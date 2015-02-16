#ifndef MODELS_PNJ_HPP
#define MODELS_PNJ_HPP

#include "graphics/drawables/map_character.hpp"
#include "models/character.hpp"

namespace models {

class PNJ : public Character,
            public graphics::MapCharacter
{
  public:

    PNJ(const std::string& filename, const sf::Vector2f& position, const sf::Vector2f size);
};

}

#endif // MODELS_PNJ_HPP
