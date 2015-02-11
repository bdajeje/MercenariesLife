#include "image.hpp"

#include <iostream>

namespace graphics {

Image::Image(const sf::Texture& texture)
{
  m_sprite.setTexture( texture );
}

void Image::draw(sf::RenderTarget& target)
{
  std::cout << "srawing to " << getPosition().x << "/" << getPosition().y << std::endl;
  m_sprite.setPosition(getPosition());
  target.draw(m_sprite);
}

void Image::resize(float width, float height)
{
  m_sprite.setScale( width / m_sprite.getTexture()->getSize().x,
                     height / m_sprite.getTexture()->getSize().y);
}

}
