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

// \todo Right now this variable is global, only because the class to handle all the following code is not yet wrapped into a class
bool window_focused = true;

void mapMovement(graphics::Map& map, models::Player& player)
{
  if( !window_focused || !map.isFocused() || map.isMoving() )
    return;

  if(sf::Keyboard::isKeyPressed( GameConfig::keyboardKey( KeyboardActions::MapMoveUp ) ))
  {
    player.setDirection(utils::Direction::Up);

    if(map.move(0, -1))
      player.move( map.timeTakenToMove() );
  }
  else if(sf::Keyboard::isKeyPressed( GameConfig::keyboardKey( KeyboardActions::MapMoveDown ) ))
  {
    player.setDirection(utils::Direction::Down);

    if( map.move(0, 1) )
      player.move( map.timeTakenToMove() );
  }
  else if(sf::Keyboard::isKeyPressed( GameConfig::keyboardKey( KeyboardActions::MapMoveLeft ) ))
  {
    player.setDirection(utils::Direction::Left);

    if( map.move(-1, 0) )
      player.move( map.timeTakenToMove() );
  }
  else if(sf::Keyboard::isKeyPressed( GameConfig::keyboardKey( KeyboardActions::MapMoveRight ) ))
  {
    player.setDirection(utils::Direction::Right);

    if( map.move(1, 0) )
      player.move( map.timeTakenToMove() );
  }
}

void mapPlayerInteraction(sf::Keyboard::Key key_code, const models::Player& player, graphics::Map& map)
{
  if( !window_focused )
    return;

  if(key_code == GameConfig::keyboardKey( KeyboardActions::MapPlayerInteraction ))
    map.playerInteraction( player.direction() );
}

int main()
{
  // Creating window
  const unsigned int window_width {1000};
  const unsigned int window_height {1000};
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
  models::Player player {"player", {(window_width - map.tileSize()) / 2, (window_height - map.tileSize()) / 2}, {map.tileSize(), map.tileSize()}};
  graphics::UserInterface ui;
  ui.setMapName(map.name());

  // Main loop
  while(window.isOpen())
  {
    // User events management
    sf::Event event;
    while(window.pollEvent(event))
    {
      switch(event.type)
      {
        case sf::Event::Closed: window.close(); break;
        case sf::Event::LostFocus: window_focused = false; break;
        case sf::Event::GainedFocus: window_focused = true; break;
        case sf::Event::KeyPressed:
        {
          // Player interact with the map
          mapPlayerInteraction(event.key.code, player, map);
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
          if( ui.startConversation( map.getPNJ(player.direction()) ))
            map.setFocused(false);
          break;
        default: break;
      }
    }

    // Map movement
    mapMovement(map, player);

    // Clear entire screen
    window.clear();

    // Draw map and player
    // Map is responsible for drawing player because of possible map z-index textures
    map.draw(window, player, window.getDefaultView());

    // Draw UI
    ui.draw(window);

    // Render screen
    window.display();
  }

  return EXIT_SUCCESS;
}
