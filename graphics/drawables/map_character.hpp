#ifndef GRAPHICS_MAP_CHARACTER_HPP
#define GRAPHICS_MAP_CHARACTER_HPP

#include <SFML/Graphics.hpp>

namespace graphics {

class MapCharacter
{
  public:

    /*! Constructor
     * \param texture - to draw
     */
    MapCharacter(const sf::Texture& texture);

    /*! Draw the character
     * \param target - where to draw
     */
    void draw(sf::RenderTarget& target);

    void setPosition(sf::Vector2f position) { m_sprite.setPosition(position); }

  protected:

    /*! Position on the map */
    sf::Vector2f m_map_position;

    /*! Character sprite */
    sf::Sprite m_sprite;
};

}

#endif // GRAPHICS_MAP_CHARACTER_HPP
