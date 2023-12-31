// Jpch
#include "Jpch.h"

// Own includes
#include "events/EventManager.h"
#include "base/Logger.h"

namespace jupiter {

UniquePtr<EventManager> gEventManager = nullptr;

void EventManager::subscribe(const EventType type, UniquePtr<IEventHandler> handler) {
    auto eventHandlers = handlersMap.find(type);
    if (eventHandlers != handlersMap.end()) {
        if (eventHandlers->second.contains(handler->getHashCode())) {
            JLOG_ERROR("Double registering of event handler with hash code {} for event type {}\n",
                       handler->getHashCode(), (int32_t)type);
            return;
        }
        eventHandlers->second.insert({handler->getHashCode(), std::move(handler)});
    } else {
        handlersMap[type].insert({handler->getHashCode(), std::move(handler)});
    }
}

void EventManager::unsubscribe(const EventType type, const uint64 handlerHash) {
    auto eventHandlers = handlersMap.find(type);
    if (eventHandlers == handlersMap.end()) {
        JLOG_ERROR("Attempting to unregister event {} that is not registered\n", (int32)type);
        return;
    }
    handlersMap[type].erase(handlerHash);
}

// TODO: implement handlersMap with vector or priority_queue as second parametar
void EventManager::triggerEvent(const Event& event) {
    auto eventHandlers = handlersMap.find(event.getType());
    if (!eventHandlers->second.empty()) {
        for (auto& [_, eventHandler] : eventHandlers->second) {
            eventHandler->execute(event);
        }
    }
}

void EventManager::queueEvent(Event* event) { eventQueue.push_back(event); }

void EventManager::dispatchEvents() {
    // Erase-remove idiom
    std::erase_if(eventQueue, [this](Event* eventPtr) {
        if (!eventPtr->handled) {
            triggerEvent(*eventPtr);
            eventPtr->handled = true;
        }
        return eventPtr->handled;
    });
}

void EventManager::shutDown() {
    // Note: all event pointers have to be created by custom allocator, that's why we dont't
    // need to worry about memory clearance here. The allocator should take care about that.
    eventQueue.clear();
    handlersMap.clear();
}

}  // namespace jupiter
