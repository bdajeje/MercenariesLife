#include <iostream>

#include <SFML/Graphics.hpp>

#include "graphics/drawables/map.hpp"
#include "graphics/textures.hpp"
#include "models/player.hpp"
#include "utils/direction.hpp"
#include "utils/resources/game_config.hpp"

using namespace utils;

void mapMovement(graphics::Map& map, models::Player& player)
{
  if( !map.isMoving() )
  {
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
}

int main()
{
  // Creating window
  const unsigned int window_width {1000};
  const unsigned int window_height {800};
  sf::RenderWindow window(sf::VideoMode(window_width, window_height), "Mercenaries Life");
  window.setFramerateLimit(60);

  // Application icon
  sf::Image icon;
  icon.loadFromFile("resources/images/icon/icon.png");
  window.setIcon(icon.getSize().x, icon.getSize().y, icon.getPixelsPtr());

  GameConfig::init();
  graphics::Textures::init("resources/images/");
  graphics::Map map {"resources/maps/1"};

  models::Player player {"player", {map.tileSize() / 2, map.tileSize() / 2}, {map.tileSize(), map.tileSize()}};

  // Main loop
  bool window_focused = true;
  while(window.isOpen())
  {
    // Events management
    sf::Event event;
    while(window.pollEvent(event))
    {
      switch(event.type)
      {
        case sf::Event::Closed: window.close(); break;
        case sf::Event::LostFocus: window_focused = false; break;
        case sf::Event::GainedFocus: window_focused = true; break;
        default: break;
      }
    }

    // If window has not the focused, skip user events
    if( window_focused )
      mapMovement(map, player);

    // Clear entire screen
    window.clear();

    // Draw map
    map.draw(window);

    // Draw player
    player.draw(window);

    //window.setView(window.getDefaultView());

    // Render screen
    window.display();
  }

  return EXIT_SUCCESS;
}
