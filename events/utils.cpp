#include "utils.hpp"

#include <iostream>
#include <map>

#include "events/playing_sound.hpp"
#include "events/to_map.hpp"

namespace events {

Type toType(const std::string& input)
{
  static const std::map<std::string, Type> bindings = {
    { "TalkToPNJ", Type::TalkToPNJ },
    { "EndTalkToPNJ", Type::EndTalkToPNJ },
    { "PlayerHere", Type::PlayerHere },
    { "PlayerTo", Type::PlayerTo },
    { "PlayerLeave", Type::PlayerLeave }
  };

  auto found = bindings.find(input);
  if( found == bindings.end() )
    return Type::None;

  return found->second;
}

std::tuple<Type, Event*> createFromJSON(const rapidjson::Value& json_event)
{
  std::string trigger = json_event["trigger"].GetString();
  Type type = toType(trigger);
  Event* event = nullptr;

  if( type != Type::None )
  {
    std::string type = json_event["type"].GetString();

    if( type == "walking_sound" )
    {
      event = new PlayingSound( json_event["values"][0u].GetString() );
    }
    else if( type == "toMap" )
    {
      event = new ToMap( json_event["values"][0u].GetString() );
    }
    else
    {
      std::cerr << "Can't create map event from " << type << std::endl;
    }
  }
  else
  {
    std::cerr << "Unknown event trigger " << trigger << std::endl;
  }

  return std::make_tuple(type, event);
}

}
