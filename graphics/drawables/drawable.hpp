#ifndef GRAPHICS_DRAWABLE_HPP
#define GRAPHICS_DRAWABLE_HPP

#include <SFML/Graphics.hpp>

namespace graphics {

class Drawable
{
  public:

    virtual ~Drawable() = default;

    virtual void draw(sf::RenderTarget& target) = 0;

    void setPosition(float x, float y) { m_position.x = x; m_position.y = y; }
    void setPosition(sf::Vector2f position) { m_position = position; }
    void move(float x, float y) { m_position.x += x; m_position.y += y; }

    const sf::Vector2f& getPosition() const { return m_position; }

  private:

    sf::Vector2f m_position;
};

}

#endif // GRAPHICS_DRAWABLE_HPP
