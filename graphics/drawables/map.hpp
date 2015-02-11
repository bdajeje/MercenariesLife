#ifndef GRAPHICS_MAP_HPP
#define GRAPHICS_MAP_HPP

#include <string>
#include <thread>
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

    /*! Is the view moving to a destination
     * \returns true if the view is actually reaching a destination
     */
    bool isMoving() const;

    /*! Smootly move the view to a target destination
     *  This method is called at each frame to create a smooth movement
     */
    void smoothViewMoveToDestination();

  private:

    /*! Map title */
    std::string m_title;

    /*! Map tiles */
    std::vector<std::vector<sf::Sprite>> m_tiles;

    /*! View of the map */
    sf::View m_view;

    /*! Clock dedicated to view movement limits */
    sf::Clock m_movement_clock;

    /*! When triggering a move, the view will smootly reach this destination */
    sf::Vector2f m_view_movement_destination;
};

}

#endif // GRAPHICS_MAP_HPP
