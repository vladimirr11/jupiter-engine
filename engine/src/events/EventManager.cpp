// Jpch
#include "Jpch.h"

// Own includes
#include "events/EventManager.h"
#include "base/Logger.h"

namespace jupiter {

UniquePtr<EventManager> gEventManager = nullptr;

void EventManager::start() {
    eventThread = std::thread(&EventManager::processEvents, this);
    jAssertExpr(!running);
    running = true;
}

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

void EventManager::triggerEvent(const Event& event) {
    if (event.getType() == EventType::WINDOW_RESIZE) {
        int stop = 10;
    }
    auto eventHandlers = handlersMap.find(event.getType());
    if (!eventHandlers->second.empty()) {
        for (auto& [_, eventHandler] : eventHandlers->second) {
            eventHandler->execute(event);
        }
    }
}

void EventManager::queueEvent(Event* event) { eventQueue.push_back(event); }

void EventManager::dispatchEvents() {
    std::unique_lock<std::mutex> lock(eventMutex);
    cv.wait(lock, [this] { return eventsProcessed || !running; });
    if (!running) {
        return;
    }
    eventsProcessed = false;
    eventsReady = true;
    lock.unlock();
    cv.notify_one();
}

void EventManager::shutDown() {
    {
        // Wait for the event processing thread to finish
        std::unique_lock<std::mutex> lock(eventMutex);
        cv.wait(lock, [this] { return eventsProcessed; });
        running = false;
    }
    cv.notify_all();
    eventThread.join();
    eventQueue.clear();
    handlersMap.clear();
}

void EventManager::processEvents() {
    for (;;) {
        // Wait until main thread queue all events
        std::unique_lock<std::mutex> lock(eventMutex);
        cv.wait(lock, [this] { return eventsReady || !running; });
        if (!running) {
            return;
        }
        eventsReady = false;

        // Process all events
        std::erase_if(eventQueue, [this](Event* eventPtr) {  // Erase-remove idiom
            if (!eventPtr->handled) {
                triggerEvent(*eventPtr);
                eventPtr->handled = true;
            }
            return eventPtr->handled;
        });
        // gMemoryArena->clear(); ///< Clear the memory arena on each frame
        eventsProcessed = true;
        lock.unlock();
        cv.notify_one();
    }
}

}  // namespace jupiter
