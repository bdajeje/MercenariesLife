#ifndef GRAPHICS_MAP_CHARACTER_HPP
#define GRAPHICS_MAP_CHARACTER_HPP

#include <SFML/Graphics.hpp>

#include "graphics/drawables/animation.hpp"
#include "utils/direction.hpp"

namespace graphics {

class MapCharacter
{
  public:

    /*! Constructor
     * \param texture_directory - directory when to find textures and animations
     * \param position          - where to draw the character
     * \param size              - size to scale textures
     * \param nbr_sprites       - number of sprites in animation
     */
    MapCharacter(const std::string& texture_directory, const sf::Vector2f& position, const sf::Vector2f& size, unsigned int nbr_sprites);

    /*! Draw the character
     * \param target - where to draw
     */
    void draw(sf::RenderTarget& target);

    /*! Movement method
     *  \param animation_time - make the animation in that amount of time, in milliseconds
     */
    void move(unsigned int animation_time);

    /*! Set direction of sprite
     *  \param direction - direction of the move
     */
    void setDirection(utils::Direction direction);

    /*! Does the character currently moving? */
    bool isMoving() const { return m_current_animation->isRunning(); }

  protected:

    /*! Character animation when moving top */
    Animation m_move_top_animation;

    /*! Character animation when moving down */
    Animation m_move_down_animation;

    /*! Character animation when moving left */
    Animation m_move_left_animation;

    /*! Character animation when moving right */
    Animation m_move_right_animation;

    /*! Pointer on the current animation */
    Animation* m_current_animation {nullptr};
};

}

#endif // GRAPHICS_MAP_CHARACTER_HPP
