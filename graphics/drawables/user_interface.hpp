#ifndef GRAPHICS_USER_INTERFACE_HPP
#define GRAPHICS_USER_INTERFACE_HPP

#include <SFML/Graphics.hpp>

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

  private:

    /*! View of the UI */
    sf::View m_view;

    /*! Name of the current map */
    sf::Text m_map_name;
};

}

#endif // GRAPHICS_USER_INTERFACE_HPP
