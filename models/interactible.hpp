#ifndef MODELS_INTERACTIBLE_HPP
#define MODELS_INTERACTIBLE_HPP

#include <functional>
#include <map>
#include <vector>

#include "events/events.hpp"

namespace models {

class Interactible
{
  public:

    Interactible() = default;

    virtual ~Interactible() = default;

    /*! Activate a specific event on this interactible
     *  \param type - to activate if available
     *  \returns true if at least one corresponding type event has been activated
     */
    bool activate(events::Type type);

    /*! Register an new event for a given type */
    void addEvent(events::Type type, std::function<void()> func);

  private:

    std::map<events::Type, std::vector<std::function<void()>>> _events;
};

}

#endif // MODELS_INTERACTIBLE_HPP
