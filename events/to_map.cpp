#include "to_map.hpp"

#include <iostream>

#include "game.hpp"

namespace events {

ToMap::ToMap( std::string map_name )
  : _map_name{map_name}
{}

bool ToMap::exec()
{
  std::cout << "to map " << _map_name << std::endl;
  Game::instance()->newMap(_map_name);

  return true;
}

}
