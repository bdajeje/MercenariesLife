#include "character.hpp"

namespace models {

Character::Character(const std::string& info_filepath)
  : m_name {info_filepath}
{
}

}
