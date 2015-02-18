#include "user_interface.hpp"

#include "graphics/fonts.hpp"
#include "utils/resources/game_config.hpp"

namespace graphics {

UserInterface::UserInterface()
{
  m_map_name.setCharacterSize(24);
  m_map_name.setFont( *Fonts::get("Ubuntu-B.ttf") );
  m_map_name.setColor(sf::Color::Red);
  m_map_name.setPosition(10, 10);
}

void UserInterface::draw(sf::RenderTarget& target)
{
  target.setView(m_view);

  // Draw map name
  target.draw(m_map_name);

  // Draw conversation
  if(m_conversation)
    m_conversation->draw(target);
}

bool UserInterface::startConversation(std::shared_ptr<models::PNJ> pnj)
{
  if(!pnj)
    return false;

  m_conversation.reset( new models::Conversation(pnj->getID(), pnj->getPortrait()) );
  return true;
}

void UserInterface::endConversation()
{
  m_conversation.reset();
}

void UserInterface::keyPress(sf::Keyboard::Key key_code)
{
  if( m_conversation )
    m_conversation->keyPress(key_code);
}

void UserInterface::keyboardAction()
{

}

}
