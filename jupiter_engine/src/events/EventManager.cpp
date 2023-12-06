// Jpch
#include "Jpch.h"

// Corresponding header
#include "events/EventManager.h"

// Own includes
#include "base/Logger.h"

namespace jupiter {

EventManager* gEventManager = nullptr;

void EventManager::subscribe(const EventType type, IEventHandler* handler) {
    auto eventHandlers = handlersMap.find(type);
    if (eventHandlers != handlersMap.end()) {
        if (eventHandlers->second.contains(handler->getHashCode())) {
            JLOG_ERROR("Double registering of event handler with hash code {} for event type {}\n",
                       handler->getHashCode(), (int32_t)type);
            return;
        }
        eventHandlers->second.insert({handler->getHashCode(), handler});
    } else {
        handlersMap[type].insert({handler->getHashCode(), handler});
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

// TODO: implement handlersMap with vector as second parametar
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
    std::erase_if(eventQueue, [this](Event* eventPtr) {
        if (!eventPtr->handled) {
            triggerEvent(*eventPtr);
        }
        return !eventPtr->handled;
    });
}

void EventManager::shutDown() { handlersMap.clear(); }

}  // namespace jupiter
