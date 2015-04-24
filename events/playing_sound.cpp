#include "playing_sound.hpp"

#include <iostream>

namespace events {

PlayingSound::PlayingSound(std::string sound_name)
  : _sound_name {sound_name}
{}

bool PlayingSound::exec()
{
  std::cout << "playing sound " << _sound_name << std::endl;
  return true;
}

}
