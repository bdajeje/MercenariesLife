#ifndef GAME_HPP
#define GAME_HPP

#include "graphics/drawables/map.hpp"
#include "graphics/drawables/user_interface.hpp"
#include "models/player.hpp"

class Game final
{
  public:

    static void init(const std::string& map_name, const std::string& player_name);

    static std::unique_ptr<Game>& instance() { return _instance; }

    void run();

    /*! Let these objects accessible everywhere */
    sf::RenderWindow _window;
    graphics::Map _map;
    std::shared_ptr<models::Player> _player;
    graphics::UserInterface _ui;
    events::KeyboardListener* _focused_object {nullptr};

  private:

    Game(unsigned int window_width, unsigned int window_height,
         const std::string& map_name, const std::string& player_name);

  private:

    static std::unique_ptr<Game> _instance;
};

#endif // GAME_HPP
