#pragma once

// Own includes
#include "events/Event.h"

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

    uint64 getHashCode() const override { return handlerCb.target_type().hash_code(); }

private:
    EventCallback<EventT> handlerCb;
};

/// @brief Creates new event handler
template <typename EventT, typename... Args>
inline UniquePtr<EventHandler<EventT>> newEventHandler(Args&&... args) {
    return newUniquePtr<EventHandler<EventT>>(std::forward<Args>(args)...);
}

}  // namespace jupiter
