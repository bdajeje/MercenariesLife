#include "interactible.hpp"

#include <iostream>

namespace models {

bool Interactible::activate(events::Type type)
{
  if( type == events::Type::None )
    return false;

  // Try to find corresponding list of events
  auto found = _events.find(type);
  if( found == _events.end() )
    return false;

  // Call each event one by one
  for( events::Event* event : found->second )
    event->exec();

  return true;
}

Interactible::~Interactible()
{
  for( auto& it : _events )
  {
    for( events::Event* event : it.second )
      delete event;
  }
}

void Interactible::addEvent(events::Type type, events::Event* event)
{
  _events[type].push_back(event);
}

}
