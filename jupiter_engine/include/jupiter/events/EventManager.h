#pragma once

// Own includes
#include "EventHandler.h"

namespace jupiter {

class EventManager {
    using EventQueue = std::vector<std::unique_ptr<Event>>;
    using EventHandlersMap =
        std::unordered_map<EventType, std::unordered_map<size_t, std::unique_ptr<IEventHandler>>>;

public:
    EventManager() = default;

    EventManager(const EventManager&) = delete;
    EventManager& operator=(const EventManager&) = delete;

    void subscribe(const EventType type, std::unique_ptr<IEventHandler>&& handler);

    void unsubscribe(const EventType type, const size_t handlerHash);

    void triggerEvent(const Event& event);

    void queueEvent(std::unique_ptr<Event>&& event);

    void dispatchEvents();

    void shutDown();

private:
    EventQueue eventQueue;
    EventHandlersMap handlersMap;
};

extern EventManager* gEventManager;

}  // namespace jupiter
