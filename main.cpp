#include <iostream>

#include <SFML/Graphics.hpp>

#include "game.hpp"

int main()
{
  Game::init("1", "player");
  Game::instance()->run();

  return EXIT_SUCCESS;
}
