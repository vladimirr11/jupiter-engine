#pragma once

// C++ system includes
#include <bitset>

// Own includes
#include "base/Defines.h"

namespace jupiter {

static constexpr uint32 kMaxComponents = 32;

struct ECRegistry;

class Entity {
public:
    Entity() = default;
    Entity(const uint32 id_, const std::bitset<kMaxComponents> components_ = {})
        : id(id_), components(components_) {}

    template <typename CompT, typename... Args>
    void assign(Args&&... args) {}

    template <typename CompT>
    void remove() {}

    const uint32 getId() const { return id; }
    const std::bitset<kMaxComponents> getComponents() const { return components; }

private:
    ECRegistry* registry = nullptr;
    const uint32 id{};
    std::bitset<kMaxComponents> components;
};

}  // namespace jupiter
