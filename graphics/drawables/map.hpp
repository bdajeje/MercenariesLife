#ifndef GRAPHICS_MAP_HPP
#define GRAPHICS_MAP_HPP

#include <string>
#include <vector>

#include <SFML/Graphics.hpp>

#include "utils/position.hpp"

namespace graphics {

class Map
{
  public:

    /*!
     * \brief Constructor with a specific file with information of the map
     * \param window_width  - width of the window
     * \param window_height - height of the window
     * \param map_filepath  - file to read to get information about the map
     * \throw on error
     */
    Map(unsigned int window_width, unsigned int window_height, const std::string& map_filepath);

    /*! Draw the map
     * \param target - where to draw
     */
    void draw(sf::RenderTarget& target);

    /*! Get map view */
    const sf::View& view() const { return m_view; }

    /*! Move the view of the map
     * \param x - movement on the X axe
     * \param y - movement on the Y axe
     */
    void move(int x, int y);

  protected:

    /*! Set title of the map
     * \param map_title - to set
     */
    void setTitle(const std::string& map_title);

    /*! Is a new move of the view allowed?
     * \returns true if we are allowed to move the view depending on time of last move
     */
    bool isMovementAllowed() const;

  private:

    /*! Map title */
    std::string m_title;

    /*! Map tiles */
    std::vector<std::vector<sf::Sprite>> m_tiles;

    /*! View of the map */
    sf::View m_view;

    /*! Clock dedicated to view movement limits */
    sf::Clock m_movement_clock;
};

}

#endif // GRAPHICS_MAP_HPP
