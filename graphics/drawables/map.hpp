#ifndef GRAPHICS_MAP_HPP
#define GRAPHICS_MAP_HPP

#include <string>
#include <thread>
#include <vector>

#include <SFML/Graphics.hpp>

#include "utils/position.hpp"

namespace graphics {

/*! Holds tile information */
struct Tile
{
  /*! Can we move onto this tile */
  bool blocking {false};
};

class Map
{
  public:

    /*!
     * \brief Constructor with a specific file with information of the map
     * \param map_name - name of the map to load
     * \throw on error
     */
    Map(const std::string& map_name);

    /*! Draw the map
     * \param target - where to draw
     */
    void draw(sf::RenderTarget& target);

    /*! Get map view */
    const sf::View& view() const { return m_view; }

    /*! Move the view of the map
     * \param x - movement on the X axe
     * \param y - movement on the Y axe
     * \return true if movement is allowed
     */
    bool move(int x, int y);

    /*! Get time taken in milliseconds to move from a tile to another
     *  \return time taken in milliseconds to move from a tile to another
     */
    unsigned int timeTakenToMove() const;

    /*! Get tile size */
    float tileSize() const { return m_tile_size; }

    /*! Is the view moving to a destination
     * \returns true if the view is actually reaching a destination
     */
    bool isMoving() const;

  protected:

    /*! Set title of the map
     * \param map_title - to set
     */
    void setTitle(const std::string& map_title);

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
    const float m_tile_size {75};

    /*! Map texture */
    sf::Texture m_map_texture;

    /*! Map sprite */
    sf::Sprite m_map_sprite;

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
