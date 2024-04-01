#pragma once

// C++ system includes
#include <unordered_map>

// Own includes
#include "events/EventHandler.h"

namespace jupiter {

class EventManager {
    using EventQueue = std::vector<Event*>;
    using EventHandlersMap =
        std::unordered_map<EventType, std::unordered_map<uint64, UniquePtr<IEventHandler>>>;

public:
    EventManager() = default;

    EventManager(const EventManager&) = delete;
    EventManager& operator=(const EventManager&) = delete;

    void subscribe(const EventType type, UniquePtr<IEventHandler> handler);
    void unsubscribe(const EventType type, const uint64 handlerHash);

    void triggerEvent(const Event& event);
    void queueEvent(Event* event);
    void dispatchEvents();

    void shutDown();

private:
    EventQueue eventQueue;
    EventHandlersMap handlersMap;
};

// Global even manager
extern UniquePtr<EventManager> gEventManager;

// Utility functions to use with _gEventManager_
template <typename EventT>
inline void subscribe(const EventCallback<EventT>& callback) {
    gEventManager->subscribe(EventT::getStaticType(), newEventHandler<EventT>(callback));
}

template <typename EventT>
inline void unsubscribe(const EventCallback<EventT>& callback) {
    gEventManager->unsubscribe(EventT::getStaticType(), callback.target_type().hash_code());
}

inline void triggerEvent(const Event& event) { gEventManager->triggerEvent(event); }

inline void queueEvent(Event* event) { gEventManager->queueEvent(event); }

inline void dispatchEvents() { gEventManager->dispatchEvents(); }

}  // namespace jupiter
