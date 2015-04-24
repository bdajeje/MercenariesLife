#include "game.hpp"

#include <iostream>

#include "events/events.hpp"
#include "graphics/fonts.hpp"
#include "graphics/textures.hpp"
#include "utils/direction.hpp"
#include "utils/resources/game_config.hpp"

using namespace utils;

std::unique_ptr<Game> Game::_instance;

void Game::init(const std::string& map_name, const std::string& player_name)
{
  if( _instance )
    return;

  GameConfig::init();
  events::Events::init();
  graphics::Textures::init("resources/images/");
  graphics::Fonts::init("resources/fonts/");

  _instance.reset( new Game( GameConfig::windowWidth(), GameConfig::windowHeight(), map_name, player_name ) );
}

Game::Game(unsigned int window_width, unsigned int window_height,
           const std::string& map_name, const std::string& player_name)
  : _window {sf::VideoMode(window_width, window_height), "Mercenaries Life"}
{
  // Creating window
  _window.setFramerateLimit(60);

  // Application icon
  sf::Image icon;
  icon.loadFromFile("resources/images/icon/icon.png");
  _window.setIcon(icon.getSize().x, icon.getSize().y, icon.getPixelsPtr());

  // Drawable objects
  _player = std::make_shared<models::Player>(player_name, sf::Vector2f{(window_width - graphics::Map::tileSize()) / 2, (window_height - graphics::Map::tileSize()) / 2},
                                                          sf::Vector2f{graphics::Map::tileSize(), graphics::Map::tileSize()});
  newMap(map_name);

  // Currently focused object
  _focused_object = _map.get();
}

void Game::run()
{
  // Main loop
  while(_window.isOpen())
  {
    // User events management
    sf::Event event;
    while(_window.pollEvent(event))
    {
      switch(event.type)
      {
        case sf::Event::Closed: _window.close(); break;
        case sf::Event::KeyPressed:
        {
          // Player interact with the map
          _focused_object->keyPress(event.key.code);
          break;
        }
        default: break;
      }
    }

    // Game events management
    while(events::Event* game_event = events::Events::pollEvent())
    {
      game_event->exec();
      delete game_event;
    }

    // Handle user key still pressed
    _focused_object->keyboardAction();

    // Clear entire screen
    _window.clear();

    // Draw map and player
    // Map is responsible for drawing player because of possible map z-index textures
    _map->draw(_window, _window.getDefaultView());

    // Draw UI
    _ui.draw(_window);

    // Render screen
    _window.display();
  }
}

void Game::newMap(const std::string& map_name)
{
  // Is the current map focused
  const bool focused = _focused_object == _map.get();

  _map.reset( new graphics::Map(map_name) );
  _map->setPlayer(_player);
  _ui.setMapName(_map->name());

  if(focused)
    setFocused(Part::Map);
}

void Game::setFocused( Part part )
{
  switch(part)
  {
    case Part::Map: _focused_object = _map.get(); break;
    case Part::UI: _focused_object = &_ui; break;
  }
}
