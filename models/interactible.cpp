#include "interactible.hpp"

#include <iostream>

namespace models {

bool Interactible::activate(events::Type type)
{
  if( type == events::Type::None )
    return false;

  std::cout << "activating " << (int)type << std::endl;

  // Try to find corresponding list of events
  auto found = _events.find(type);
  if( found == _events.end() )
    return false;

  // Call each event one by one
  for( const auto& func : found->second )
    func();

  return true;
}

void Interactible::addEvent(events::Type type, std::function<void()> func)
{
  _events[type].push_back(func);
}

}
