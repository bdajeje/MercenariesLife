#ifndef EVENTS_PLAYINGSOUND_HPP
#define EVENTS_PLAYINGSOUND_HPP

#include "events/events.hpp"

namespace events {

class PlayingSound final : public Event
{
  public:

    PlayingSound(std::string sound_name);

    virtual bool exec();

  private:

    std::string _sound_name;
};

}

#endif // EVENTS_PLAYINGSOUND_HPP
