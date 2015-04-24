#ifndef EVENTS_UTILS_HPP
#define EVENTS_UTILS_HPP

#include "events/events.hpp"
#include "utils/rapidjson/document.h"

namespace events {

Type toType(const std::string& input);
std::tuple<Type, Event*> createFromJSON(const rapidjson::Value& json_event);

}

#endif // EVENTS_UTILS_HPP

