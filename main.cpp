#include <iostream>

#include <SFML/Graphics.hpp>

#include "graphics/drawables/map.hpp"
#include "graphics/textures.hpp"
#include "models/player.hpp"
#include "utils/resources/game_config.hpp"

int main()
{
  using namespace utils;

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
  graphics::Map map {window_width, window_height, utils::GameConfig::mapTileSize(), "resources/maps/1"};

  const float map_tile_size = GameConfig::mapTileSize();
  models::Player player {"player", { (window_width - map_tile_size) / 2, (window_height - map_tile_size) / 2 }};

  // Main loop
  while(window.isOpen())
  {
    // Events management
    sf::Event event;
    while(window.pollEvent(event))
    {
      if(event.type == sf::Event::Closed)
        window.close();
    }

    // Handling map movement
    if(sf::Keyboard::isKeyPressed( GameConfig::keyboardKey( KeyboardActions::MapMoveUp ) ))
      map.move(0, -1);
    else if(sf::Keyboard::isKeyPressed( GameConfig::keyboardKey( KeyboardActions::MapMoveDown ) ))
      map.move(0, 1);
    else if(sf::Keyboard::isKeyPressed( GameConfig::keyboardKey( KeyboardActions::MapMoveLeft ) ))
      map.move(-1, 0);
    else if(sf::Keyboard::isKeyPressed( GameConfig::keyboardKey( KeyboardActions::MapMoveRight ) ))
      map.move(1, 0);

    // Clear entire screen
    window.clear();

    // Draw map
    window.setView(map.view());
    map.draw(window);

    // Draw player
    window.setView(window.getDefaultView());
    player.draw(window);

    // Render screen
    window.display();
  }

  return EXIT_SUCCESS;
}
