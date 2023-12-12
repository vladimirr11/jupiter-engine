#pragma once

// Own includes
#include "Event.h"

namespace jupiter {

class IEventHandler {
public:
    virtual ~IEventHandler() = default;

    virtual void execute(const Event& event) = 0;

    virtual uint64 getHashCode() const = 0;
};

template <typename EventT>
class EventHandler : public IEventHandler {
public:
    EventHandler(const EventCallback<EventT>& callback) : handlerCb(callback) {}

    void execute(const Event& event) override {
        if (event.getType() == EventT::getStaticType()) {
            handlerCb(static_cast<const EventT&>(event));
        }
    }

    size_t getHashCode() const override { return handlerCb.target_type().hash_code(); }

private:
    EventCallback<EventT> handlerCb;
};

/// @brief Creates new event handler in pre-allocated memory
template <typename EventT, typename... Args>
inline EventHandler<EventT>* newEventHandler(Args&&... args) {
    return gLinearAllocator->create<EventHandler<EventT>>(std::forward<Args>(args)...);
}

}  // namespace jupiter
