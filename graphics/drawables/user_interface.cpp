#include "user_interface.hpp"

#include "graphics/fonts.hpp"

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
  target.draw(m_map_name);
}

bool UserInterface::startConversation(std::shared_ptr<models::PNJ> pnj)
{
  if(!pnj)
    return false;

  m_conversation = models::Conversation::loadConversation(pnj->getID());
  return true;
}

}
