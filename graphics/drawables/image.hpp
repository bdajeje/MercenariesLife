#ifndef GRAPHICS_IMAGE_HPP
#define GRAPHICS_IMAGE_HPP

#include <SFML/Graphics.hpp>

#include "graphics/drawables/drawable.hpp"

namespace graphics {

class Image : public Drawable
{
  public:

    Image(const sf::Texture& texture);

    void draw(sf::RenderTarget& target);

    void resize(float width, float height);

  private:

    sf::Sprite m_sprite;
};

}

#endif // GRAPHICS_IMAGE_HPP
