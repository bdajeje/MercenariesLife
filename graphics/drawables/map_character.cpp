#include "map_character.hpp"

#include "graphics/textures.hpp"
#include "utils/resources/game_config.hpp"

#include <iostream>

namespace graphics {

MapCharacter::MapCharacter(const std::string& texture_directory, const sf::Vector2f& position, const sf::Vector2f& size, unsigned int nbr_sprites)
  : m_move_top_animation { *Textures::get("characters/" + texture_directory + "/move_top.png"), size, nbr_sprites }
  , m_move_down_animation { *Textures::get("characters/" + texture_directory + "/move_bottom.png"), size, nbr_sprites }
  , m_move_left_animation { *Textures::get("characters/" + texture_directory + "/move_left.png"), size, nbr_sprites }
  , m_move_right_animation { *Textures::get("characters/" + texture_directory + "/move_right.png"), size, nbr_sprites }
  , m_current_animation { &m_move_down_animation }
{
  m_move_top_animation.setPosition(position);
  m_move_down_animation.setPosition(position);
  m_move_left_animation.setPosition(position);
  m_move_right_animation.setPosition(position);
}

void MapCharacter::draw(sf::RenderTarget& target)
{
  target.draw(*m_current_animation);
}

void MapCharacter::setDirection(utils::Direction direction)
{
  switch(direction)
  {
    case utils::Direction::Up:    m_current_animation = &m_move_top_animation; break;
    case utils::Direction::Down:  m_current_animation = &m_move_down_animation; break;
    case utils::Direction::Left:  m_current_animation = &m_move_left_animation; break;
    case utils::Direction::Right: m_current_animation = &m_move_right_animation; break;
  }
}

void MapCharacter::move(unsigned int animation_time)
{
  m_current_animation->start( animation_time, false );
}

}
