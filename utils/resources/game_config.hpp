#ifndef UTILS_GAME_CONFIG_HPP
#define UTILS_GAME_CONFIG_HPP

#include <map>
#include <memory>

#include <SFML/Graphics.hpp>

namespace utils {

/*! Every possible keyboard actions */
enum class KeyboardActions
{
  MapMoveUp, MapMoveDown, MapMoveLeft, MapMoveRight, MapPlayerInteraction
};

class GameConfig final
{
  public:

    /*! Init method to call before using this singleton */
    static void init();

    /*! Get map tile size */
    //static float mapTileSize() { return s_instance->m_map_tile_size; }

    /*! Get keyboard key from a keyboard action */
    static sf::Keyboard::Key keyboardKey(KeyboardActions action) { return s_instance->m_key_bingings[action]; }

    /*! Get map movement speed */
    static float mapMovementTilesPerSecond() { return s_instance->m_map_movement_speed; }

  private:

    GameConfig();

  private:

    /*! Size (width and height) of a map tile */
    //float m_map_tile_size {75};

    /*! Speed of map movement in tiles per second */
    float m_map_movement_speed {3};

    /*! Keyboard actions mapped to keys */
    std::map<KeyboardActions, sf::Keyboard::Key> m_key_bingings;

    /*! Unique instance */
    static std::unique_ptr<GameConfig> s_instance;
};

}

#endif // UTILS_GAME_CONFIG_HPP
