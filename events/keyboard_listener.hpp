#ifndef EVENTS_KEYBOARD_LISTENER_HPP
#define EVENTS_KEYBOARD_LISTENER_HPP

#include <SFML/Graphics.hpp>

namespace events {

class KeyboardListener
{
  public:

    KeyboardListener() = default;

    virtual void keyPress(sf::Keyboard::Key key_code) = 0;
    virtual void keyboardAction() = 0;
};

}

#endif // EVENTS_KEYBOARD_LISTENER_HPP
