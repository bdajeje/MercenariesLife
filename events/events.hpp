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
  PlayerEnter, PlayerLeave
};

class Events final
{
  public:

    /*! Init singleton */
    static void init();

    /*! Poll first event */
    static bool pollEvent(Type& type);

    /*! Add an event to the queue */
    static void addEvent(Type type) { s_instance->m_events.push(type); }

  private:

    Events() = default;

  private:

    /*! Events queue (FIFO) */
    std::queue<Type> m_events;

    /*! Unique instance */
    static std::unique_ptr<Events> s_instance;
};

}

#endif // EVENTS_EVENTS_HPP
