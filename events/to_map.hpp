#ifndef TOMAP_HPP
#define TOMAP_HPP

#include "events/events.hpp"

namespace events {

class ToMap : public Event
{
  public:

    ToMap(std::string map_name);

    virtual bool exec();

  private:

    std::string _map_name;
};

}

#endif // TOMAP_HPP
