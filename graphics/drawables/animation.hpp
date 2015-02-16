#ifndef GRAPHICS_ANIMATION_HPP
#define GRAPHICS_ANIMATION_HPP

#include <SFML/Graphics.hpp>

namespace graphics {

class Animation final : public sf::Drawable
{
  public:

    /*!
     * \brief Animation constructor
     * \param texture_filepath - texture file
     * \param sizes            - scale textures to fit this size
     * \param nbr_sprites      - number of sprites inside the texture
     */
    Animation(const std::string& texture_filepath, const sf::Vector2f& sizes, unsigned int nbr_sprites);

    /*! Start the animation frome the beginning
     *  \param animation_time - animation will complete in given time
     *  \param repeat         - do we want the animation to repeat
     */
    void start(unsigned int animation_time, bool repeat);

    /*! Is the application currently playing */
    bool isRunning() const { return m_started; }

  protected:

    /*! See parent class */
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

  private:

    /*! Choose which sprite to draw */
    void updateCurrentSprite() const;

    /*! Select subsprite from bigsprite depending on m_current_sprite */
    void selectSubSprite() const;

  private:

    /*! Sprite of the animation containing all other sprites */
    mutable sf::Sprite m_animation_sprite;

    /*! Number of sub sprites inside m_animation_sprite */
    unsigned int m_nbr_sprites;

    /*! Current sprite to draw in m_sprites */
    mutable size_t m_current_sprite {0};

    /*! Repeat the animation after finished */
    bool m_repeat;

    /*! Is the animation started? */
    mutable bool m_started {false};

    /*! Animation clock */
    mutable sf::Clock m_clock;

    /*! Time between sprites in milliseconds */
    int m_time_between_sprite;
};

}

#endif // GRAPHICS_ANIMATION_HPP
