#include "character.hpp"

namespace models {

Character::Character(const std::string& info_filename)
  : m_name {"resources/characters/" + info_filename}
{
}

}
