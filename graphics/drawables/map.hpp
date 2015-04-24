#ifndef GRAPHICS_MAP_HPP
#define GRAPHICS_MAP_HPP

#include <string>
#include <thread>
#include <vector>

#include <SFML/Graphics.hpp>

#include "events/keyboard_listener.hpp"
#include "models/interactible.hpp"
#include "models/pnj.hpp"
#include "models/player.hpp"
#include "utils/position.hpp"

namespace graphics {

/*! Holds tile information */
class Tile : public models::Interactible
{
  public:

    /*! Can we move onto this tile */
    bool blocking {false};

    /*! Possible PNJ on this tile */
    std::shared_ptr<models::PNJ> pnj;
};

class Map final : public events::KeyboardListener
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
    void draw(sf::RenderTarget& target, const sf::View& player_view);

    /*! Move the view of the map
     * \param x - movement on the X axe
     * \param y - movement on the Y axe
     * \return true if movement is allowed
     */
    bool move(int x, int y);

    /*! Player interacts with a tile
     *  \param direction - of the interactions, usefull to know which tile is targeted
     */
    void playerInteraction(utils::Direction direction);

    /*! Set a player object to interact to with the map */
    void setPlayer(std::shared_ptr<models::Player>& player) { m_player = player; }

    /*! Get tile size */
    float tileSize() const { return m_tile_size; }

    /*! Get map name */
    const std::string& name() const { return m_map_name; }

    /*! Get PNJ in a direction from current position
     *  \param direction - where to search
     *  \return found pnj or nullptr
     */
    std::shared_ptr<models::PNJ> getPNJ(utils::Direction direction) const;

    /*! Is the view moving to a destination
     * \returns true if the view is actually reaching a destination
     */
    bool isMoving() const;

    /*! Implementations for KeyboardListener */
    virtual void keyPress(sf::Keyboard::Key key_code);
    virtual void keyboardAction();

    // TMP
    static void toMap(int map_sumber);

  private:

    /*! Set title of the map
     * \param map_title - to set
     */
    void setMapName(const std::string& map_title);

    /*! Can we move to destination
     * \returns true if we can move to destination
     */
    bool canMoveTo(int x, int y) const;

    /*! Does a specific couple of x/y targets a valid tile */
    bool isValidPosition(int x, int y) const;

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

    /*!
     * \brief Get top left corner position in pixel of a tile from a tile position
     * \param tile_position - to find pixel position from
     * \return position in pixel
     */
    sf::Vector2f tileCornerPositionInPixel(const utils::Position& tile_position) const;

    /*! Load PNJs
     *  \param pnjs_filepath - filepath to PNJs file
     */
    void loadPNJs(const std::string& pnjs_filepath);

    /*! Get time taken in milliseconds to move from a tile to another
     *  \return time taken in milliseconds to move from a tile to another
     */
    unsigned int timeTakenToMove() const;

    /*! Get a tile by its coordinates */
    Tile& getTile(size_t x, size_t y) { return m_tiles[y][x]; }
    const Tile& getTile(size_t x, size_t y) const { return m_tiles[y][x]; }

    Tile& getCurrentTile() { return m_tiles[m_tile_position.y][m_tile_position.x]; }

    /*! Call this method when the move destination is reached */
    void moveDestinationReached();

  private:

    /*! Width/Height of a tile */
    const float m_tile_size {75};

    /*! Map texture */
    sf::Texture m_map_texture;

    /*! Map sprite */
    sf::Sprite m_map_sprite;

    /*! Map title */
    std::string m_map_name;

    /*! Map tiles */
    std::vector<std::vector<Tile>> m_tiles;

    /*! On which tile the view is currently centered */
    utils::Position m_tile_position;

    /*! View of the map */
    sf::View m_view;

    /*! Clock dedicated to view movement limits */
    sf::Clock m_movement_clock;

    /*! PNJs of this map */
    std::vector<std::shared_ptr<models::PNJ>> m_pnjs;

    /*! Player object */
    std::shared_ptr<models::Player> m_player;
};

}

#endif // GRAPHICS_MAP_HPP
