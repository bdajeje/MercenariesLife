#include "game.hpp"

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
  , _map{map_name}
{
  // Creating window
  _window.setFramerateLimit(60);

  // Application icon
  sf::Image icon;
  icon.loadFromFile("resources/images/icon/icon.png");
  _window.setIcon(icon.getSize().x, icon.getSize().y, icon.getPixelsPtr());

  // Drawable objects
  _player = std::make_shared<models::Player>(player_name, sf::Vector2f{(window_width - _map.tileSize()) / 2, (window_height - _map.tileSize()) / 2},
                                                          sf::Vector2f{_map.tileSize(), _map.tileSize()});
  _map.setPlayer(_player);
  _ui.setMapName(_map.name());

  // Currently focused object
  _focused_object = &_map;
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
    _map.draw(_window, _window.getDefaultView());

    // Draw UI
    _ui.draw(_window);

    // Render screen
    _window.display();
  }
}
