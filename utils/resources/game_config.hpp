#ifndef UTILS_GAME_CONFIG_HPP
#define UTILS_GAME_CONFIG_HPP

#include <map>
#include <memory>

#include <SFML/Graphics.hpp>

namespace utils {

/*! Every possible keyboard actions */
enum class KeyboardActions
{
  MapMoveUp, MapMoveDown, MapMoveLeft, MapMoveRight, MapPlayerInteraction,
  ShowAllConversation, ConversationChoiceUp, ConversationChoiceDown, ConversationSelectChoice
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

    /*! Get display conversation character speed
     *  \return number of characters to display per second
     */
    static float conversationCharactersPerSecond() { return s_instance->m_conversation_characters_speed; }

    /*! Window sizes */
    static unsigned int windowWidth() { return 1000; }
    static unsigned int windowHeight() { return 1000; }

  private:

    GameConfig();

  private:

    /*! Size (width and height) of a map tile */
    //float m_map_tile_size {75};

    /*! Speed of map movement in tiles per second */
    float m_map_movement_speed {3};

    /*! Number of character to display in a conversation per second */
    float m_conversation_characters_speed {50};

    /*! Keyboard actions mapped to keys */
    std::map<KeyboardActions, sf::Keyboard::Key> m_key_bingings;

    /*! Unique instance */
    static std::unique_ptr<GameConfig> s_instance;
};

}

#endif // UTILS_GAME_CONFIG_HPP
