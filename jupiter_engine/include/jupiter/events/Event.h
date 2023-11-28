#pragma once

// C++ system includes
#include <string>

// Own includes
#include "EventDefines.h"

namespace jupiter {

class Event {
public:
    virtual ~Event() = default;

    virtual EventType getType() const = 0;

    virtual std::string toString() const = 0;

public:
    bool handled = false;
};

}  // namespace jupiter