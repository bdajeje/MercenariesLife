#include "game_config.hpp"

namespace utils {

std::unique_ptr<GameConfig> GameConfig::s_instance;

void GameConfig::init()
{
  if(s_instance)
    return;

  s_instance.reset( new GameConfig() );
}

GameConfig::GameConfig()
{
  // Map movements
  m_key_bingings[KeyboardActions::MapMoveUp] = sf::Keyboard::Up;
  m_key_bingings[KeyboardActions::MapMoveDown] = sf::Keyboard::Down;
  m_key_bingings[KeyboardActions::MapMoveLeft] = sf::Keyboard::Left;
  m_key_bingings[KeyboardActions::MapMoveRight] = sf::Keyboard::Right;

  // Map interaction
  m_key_bingings[KeyboardActions::MapPlayerInteraction] = sf::Keyboard::Space;

  // Conversations
  m_key_bingings[KeyboardActions::ShowAllConversation] = sf::Keyboard::Space;
  m_key_bingings[KeyboardActions::ConversationChoiceUp] = sf::Keyboard::Up;
  m_key_bingings[KeyboardActions::ConversationChoiceDown] = sf::Keyboard::Down;
  m_key_bingings[KeyboardActions::ConversationSelectChoice] = sf::Keyboard::Return;
}

}
