#pragma once

// C++ system includes
#include <unordered_map>

// Own includes
#include "EventHandler.h"

namespace jupiter {

class EventManager {
    using EventQueue = std::vector<Event*>;
    using EventHandlersMap =
        std::unordered_map<EventType, std::unordered_map<size_t, IEventHandler*>>;

public:
    EventManager() = default;

    EventManager(const EventManager&) = delete;
    EventManager& operator=(const EventManager&) = delete;

    void subscribe(const EventType type, IEventHandler* handler);

    void unsubscribe(const EventType type, const size_t handlerHash);

    void triggerEvent(const Event& event);

    void queueEvent(Event* event);

    void dispatchEvents();

    void shutDown();

private:
    EventQueue eventQueue;
    EventHandlersMap handlersMap;
};

extern EventManager* gEventManager;

}  // namespace jupiter
