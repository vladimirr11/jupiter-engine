#pragma once

// S++ system icnludes
#include <functional>

// Own includes
#include "EventDefines.h"
#include "base/BaseDefines.h"
#include "memory/LinearAllocator.h"

// Third-party includes
#define FMT_HEADER_ONLY
#include <fmt/format.h>

namespace jupiter {

/// @brief Alias template for function that will be called by a subscriber (handler) of event
template <typename EventT>
using EventCallback = std::function<void(const EventT&)>;

class Event {
public:
    virtual ~Event() = default;

    virtual EventType getType() const = 0;

    virtual std::string toString() const = 0;

public:
    bool handled = false;
};

#define EVENT_TYPE(EventT)                                     \
    static_assert(std::is_same_v<decltype(EventT), EventType>, \
                  "provided value is not an EventType");       \
    static EventType getStaticType() { return EventT; }        \
    virtual EventType getType() const override { return getStaticType(); }

/// @brief Creates every event in pre-allocated memory
template <typename EventT, typename... Args>
inline EventT* newEvent(Args&&... args) {
    return gLinearAllocator->create<EventT>(std::forward<Args>(args)...);
}

}  // namespace jupiter