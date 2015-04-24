#ifndef EVENTS_TALKTOPNJ_HPP
#define EVENTS_TALKTOPNJ_HPP

#include "events/events.hpp"
#include "models/pnj.hpp"

namespace events {

class TalkToPNJ : public Event
{
  public:

    TalkToPNJ( std::shared_ptr<models::PNJ>& pnj );

    virtual bool exec();

  private:

    std::shared_ptr<models::PNJ> _pnj;
};

}

#endif // EVENTS_TALKTOPNJ_HPP
