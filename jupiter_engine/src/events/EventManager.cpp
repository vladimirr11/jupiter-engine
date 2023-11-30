// Jpch
#include "jupiter/Jpch.h"

// Corresponding header
#include "jupiter/events/EventManager.h"

// Own includes
#include "jupiter/base/Logger.h"

namespace jupiter {

EventManager* gEventManager = nullptr;

void EventManager::subscribe(const EventType type, std::unique_ptr<IEventHandler>&& handler) {
    auto eventHandlers = handlersMap.find(type);
    if (eventHandlers != handlersMap.end()) {
        if (eventHandlers->second.contains(handler->getHashCode())) {
            LOG_ERROR("Double registering of event handler with hash code {} for event type {}\n",
                      handler->getHashCode(), (int32_t)type);
            return;
        }
        eventHandlers->second.insert({handler->getHashCode(), std::move(handler)});
    } else {
        handlersMap[type].insert({handler->getHashCode(), std::move(handler)});
    }
}

void EventManager::unsubscribe(const EventType type, const size_t handlerHash) {
    auto eventHandlers = handlersMap.find(type);
    if (eventHandlers == handlersMap.end()) {
        LOG_ERROR("Attempting to unregister event {} that is not registered\n", (int32_t)type);
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

void EventManager::queueEvent(std::unique_ptr<Event>&& event) {
    eventQueue.push_back(std::move(event));
}

void EventManager::dispatchEvents() {
    std::erase_if(eventQueue, [this](std::unique_ptr<Event>& eventPtr) {
        if (!eventPtr->handled) {
            triggerEvent(*eventPtr.get());
        }
        return !eventPtr->handled;
    });
}

void EventManager::shutDown() { handlersMap.clear(); }

}  // namespace jupiter
