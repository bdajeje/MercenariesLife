#ifndef GRAPHICS_MAP_HPP
#define GRAPHICS_MAP_HPP

#include <string>
#include <thread>
#include <vector>

#include <SFML/Graphics.hpp>

#include "utils/position.hpp"

namespace graphics {

struct Tile
{
  /*! Can we move onto this tile */
  bool blocking {false};

  /*! Sprite of the tile */
  sf::Sprite sprite;
};

class Map
{
  public:

    /*!
     * \brief Constructor with a specific file with information of the map
     * \param window_width  - width of the window
     * \param window_height - height of the window
     * \param tile_size     - widht and height of a tile
     * \param map_filepath  - file to read to get information about the map
     * \throw on error
     */
    Map(unsigned int window_width, unsigned int window_height, unsigned int tile_size, const std::string& map_filepath);

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

    /*! Can we move to destination
     * \returns true if we can move to destination
     */
    bool canMoveTo(int x, int y) const;

    /*! Smootly move the view to a target destination
     *  This method is called at each frame to create a smooth movement
     */
    void smoothViewMoveToDestination();

    /*!
     * \brief Get center position in pixel of a tile from a tile position
     * \param tile_position - to find pixel position from
     * \return position in pixel
     */
    sf::Vector2f tileCenterPositionInPixel(const utils::Position& tile_position) const;

  private:

    /*! Width/Height of a tile */
    const unsigned int m_tile_size {75};

    /*! Map title */
    std::string m_title;

    /*! Map tiles */
    std::vector<std::vector<Tile>> m_tiles;

    /*! On which tile the view is currently centered */
    utils::Position m_tile_position;

    /*! View of the map */
    sf::View m_view;

    /*! Clock dedicated to view movement limits */
    sf::Clock m_movement_clock;
};

}

#endif // GRAPHICS_MAP_HPP
