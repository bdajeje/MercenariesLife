#ifndef GRAPHICS_USER_INTERFACE_HPP
#define GRAPHICS_USER_INTERFACE_HPP

#include <SFML/Graphics.hpp>

#include "models/conversation.hpp"
#include "models/pnj.hpp"

namespace graphics {

class UserInterface
{
  public:

    UserInterface();

    /*! Draw the UI
     * \param target - where to draw
     */
    void draw(sf::RenderTarget& target);

    /*! Update the map name */
    void setMapName(const std::string& name) { m_map_name.setString(name); }

    /*! Start a conversation with a PNJ
     *  \param pnj - to start the conversation with
     * \return true with the conversation is started, false otherwise (invalid PNJ for example)
     */
    bool startConversation(std::shared_ptr<models::PNJ> pnj);

  private:

    /*! View of the UI */
    sf::View m_view;

    /*! Name of the current map */
    sf::Text m_map_name;

    /*! Currently played conversation */
    std::shared_ptr<models::Conversation> m_conversation;
};

}

#endif // GRAPHICS_USER_INTERFACE_HPP
