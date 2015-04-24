#ifndef EVENTS_ENDTALKTOPNJ_HPP
#define EVENTS_ENDTALKTOPNJ_HPP

#include "events/events.hpp"
#include "models/pnj.hpp"

namespace events {

class EndTalkToPNJ : public Event
{
  public:

    virtual bool exec();
};

}

#endif // EVENTS_ENDTALKTOPNJ_HPP
