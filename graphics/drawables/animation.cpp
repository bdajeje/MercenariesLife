#include "animation.hpp"

#include <iostream>

#include "graphics/textures.hpp"

namespace graphics {

Animation::Animation(const std::string& texture_filepath, const sf::Vector2f& sizes, unsigned int nbr_sprites)
  : m_nbr_sprites {nbr_sprites}
{
  const sf::Texture* texture = Textures::get(texture_filepath);
  if(!texture)
  {
    std::cerr << "Animation can't load texture: " << texture_filepath << std::endl;
    return;
  }

  m_animation_sprite.setTexture(*texture);
  m_animation_sprite.setScale( (sizes.x * nbr_sprites) / texture->getSize().x,
                               sizes.y / texture->getSize().y );

  // Select first sprite by default
  selectSubSprite();
}

void Animation::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
  // See if you need to change sprite
  if( isRunning() )
    updateCurrentSprite();

  target.draw(m_animation_sprite, states);
}

void Animation::start(unsigned int animation_time, bool repeat)
{
  m_repeat = repeat;
  m_current_sprite = 0;
  m_time_between_sprite = animation_time / m_nbr_sprites;
  m_started = true;
  m_clock.restart();
}

void Animation::updateCurrentSprite() const
{
  const sf::Time elapsed_time = m_clock.getElapsedTime();
  if( elapsed_time.asMilliseconds() > m_time_between_sprite )
  {
    m_current_sprite++;
    if(m_current_sprite >= m_nbr_sprites)
    {
      m_current_sprite = 0;

      // If not repeat animation, stop it
      if( !m_repeat )
        m_started = false;
    }

    selectSubSprite();
    m_clock.restart();
  }
}

void Animation::selectSubSprite() const
{
  // Select subsprite from big sprite
  const auto& size = m_animation_sprite.getTexture()->getSize();
  const auto witdh = size.x / m_nbr_sprites;
  m_animation_sprite.setTextureRect(sf::IntRect(m_current_sprite * witdh, 0, witdh, size.y));
}

}
