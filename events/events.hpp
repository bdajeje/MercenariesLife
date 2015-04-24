#ifndef EVENTS_EVENTS_HPP
#define EVENTS_EVENTS_HPP

#include <memory>
#include <queue>

namespace events {

enum class Type {
  None,

  /*! NPJ interactions */
  TalkToPNJ, EndTalkToPNJ,

  /*! Map interactions */
  PlayerHere, // Player is fully here (end of the move)
  PlayerTo,   // Player comes to
  PlayerLeave // Player starts leaving
};

class Event
{
  public:

    //Event(Type trigger);
    Event() = default;

    virtual ~Event() = default;

    /*! Call this method to exec the event
     *  \returns true if the event has been executed succesfully
     */
    virtual bool exec() = 0;
};

class Events final
{
  public:

    /*! Init singleton */
    static void init();

    /*! Poll first event
     *  WARNING: YOU HAVE TO DELETE THE GIVEN POINTER YOURSELF
     *           I had issues with polymosphism and std::shared_ptr
     *  \todo fix upper warning message
     */
    static Event* pollEvent();

    /*! Add an event to the queue */
    static void addEvent(Event* event) { s_instance->m_events.push(event); }

  private:

    Events() = default;

  private:

    /*! Events queue (FIFO) */
    std::queue<Event*> m_events;

    /*! Unique instance */
    static std::unique_ptr<Events> s_instance;
};

}

#endif // EVENTS_EVENTS_HPP
