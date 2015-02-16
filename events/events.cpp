#include "events.hpp"

namespace events {

std::unique_ptr<Events> Events::s_instance;

void Events::init()
{
  if(s_instance)
    return;

  s_instance.reset(new Events);
}

bool Events::pollEvent(Type &type)
{
  if(s_instance->m_events.empty())
    return false;

  type = s_instance->m_events.front();
  s_instance->m_events.pop();

  return true;
}

}
