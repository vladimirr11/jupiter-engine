#pragma once

// Own includes
#include "EventDefines.h"

// Third-party includes
#define FMT_HEADER_ONLY
#include <fmt/format.h>

namespace jupiter {

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

}  // namespace jupiter