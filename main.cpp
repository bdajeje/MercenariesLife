#include <iostream>

#include <SFML/Graphics.hpp>

#include "events/events.hpp"
#include "graphics/drawables/map.hpp"
#include "graphics/drawables/user_interface.hpp"
#include "graphics/fonts.hpp"
#include "graphics/textures.hpp"
#include "models/player.hpp"
#include "utils/direction.hpp"
#include "utils/resources/game_config.hpp"

using namespace utils;

int main()
{
  // Creating window
  const unsigned int window_width = GameConfig::windowWidth();
  const unsigned int window_height = GameConfig::windowHeight();
  sf::RenderWindow window(sf::VideoMode(window_width, window_height), "Mercenaries Life");
  window.setFramerateLimit(60);

  // Application icon
  sf::Image icon;
  icon.loadFromFile("resources/images/icon/icon.png");
  window.setIcon(icon.getSize().x, icon.getSize().y, icon.getPixelsPtr());

  GameConfig::init();
  events::Events::init();
  graphics::Textures::init("resources/images/");
  graphics::Fonts::init("resources/fonts/");

  // Drawable objects
  graphics::Map map {"1"};
  auto player = std::make_shared<models::Player>("player", sf::Vector2f{(window_width - map.tileSize()) / 2, (window_height - map.tileSize()) / 2},
                                                           sf::Vector2f{map.tileSize(), map.tileSize()});
  map.setPlayer(player);
  graphics::UserInterface ui;
  ui.setMapName(map.name());

  // Currently focused object
  events::KeyboardListener* focused_object = &map;

  // Main loop
  bool window_focused = true;
  while(window.isOpen())
  {
    // User events management
    sf::Event event;
    while(window.pollEvent(event))
    {
      if(!window_focused)
        continue;

      switch(event.type)
      {
        case sf::Event::Closed: window.close(); break;
        case sf::Event::LostFocus: window_focused = false; break;
        case sf::Event::GainedFocus: window_focused = true; break;
        case sf::Event::KeyPressed:
        {
          // Player interact with the map
          focused_object->keyPress(event.key.code);
          break;
        }
        default: break;
      }
    }

    // Game events management
    events::Type game_event;
    while(events::Events::pollEvent(game_event))
    {
      switch(game_event)
      {
        case events::Type::TalkToPNJ:
          if( ui.startConversation( map.getPNJ(player->direction()) ))
            focused_object = &ui;
          break;
        case events::Type::EndTalkToPNJ:
        {
          ui.endConversation();
          focused_object = &map;
          break;
        }
        default: break;
      }
    }

    // Handle user key still pressed
    focused_object->keyboardAction();

    // Clear entire screen
    window.clear();

    // Draw map and player
    // Map is responsible for drawing player because of possible map z-index textures
    map.draw(window, window.getDefaultView());

    // Draw UI
    ui.draw(window);

    // Render screen
    window.display();
  }

  return EXIT_SUCCESS;
}
