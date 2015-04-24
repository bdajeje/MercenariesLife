#include "events.hpp"

#include <map>

namespace events {

std::unique_ptr<Events> Events::s_instance;

void Events::init()
{
  if(s_instance)
    return;

  s_instance.reset(new Events);
}

Event* Events::pollEvent()
{
  if(s_instance->m_events.empty())
    return nullptr;

  auto& event = s_instance->m_events.front();
  s_instance->m_events.pop();

  return event;
}

}
