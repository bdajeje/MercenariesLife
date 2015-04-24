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

bool Events::pollEvent(Type &type)
{
  if(s_instance->m_events.empty())
    return false;

  type = s_instance->m_events.front();
  s_instance->m_events.pop();

  return true;
}

//Type stringToType(const std::string& input)
//{
//  static const std::map<std::string, Type> mapping = {
//    "toMap", Type::ToMap
//  };

//  auto found = mapping.find(input);
//  if( found == mapping.end() )
//  {
//    std::cerr << "type::stringToType error, unknown type: " << input << std::endl;
//    return Type::None;
//  }

//  return found.second;
//}

}
