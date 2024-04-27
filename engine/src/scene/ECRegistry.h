#pragma once

// C++ system includes
#include <bitset>
#include <type_traits>

// Own includes
#include "base/Defines.h"

namespace jupiter {

static constexpr uint32 kMaxComponents = 32;

struct ECRegistry;

class Entity {
public:
    Entity() = default;
    Entity(const uint32 id_, ECRegistry* registry_,
           const std::bitset<kMaxComponents> components_ = {})
        : registry(registry_), id(id_), components(components_) {}

    // Note: not allowed entities with same id
    Entity(const Entity& other) = delete;
    Entity& operator=(const Entity& rhs) = delete;

    // Initialization of default constructed entities
    void init(const uint32 id_, ECRegistry* registry_,
              const std::bitset<kMaxComponents> components_ = {}) {
        registry = registry_;
        id = id_;
        components = components_;
    }

    // Copy _*this_ with different id
    Entity clone() {}

    template <typename CompT, typename... Args>
    void assign(Args&&... args) {}

    template <typename CompT>
    void remove() {}

    const uint32 getId() const { return id; }
    const std::bitset<kMaxComponents> getComponents() const { return components; }

private:
    ECRegistry* registry = nullptr;
    uint32 id{};
    std::bitset<kMaxComponents> components;
};

/// @brief Used to retrieve unique component type id
struct ComponentFamily {
public:
    template <typename Type>
    inline static uint32 getTypeId() {
        return getIdentifier<std::remove_cvref_t<Type>>();
    }

private:
    template <typename...>
    static uint32 getIdentifier() {
        static const uint32 value = id++;
        return value;
    }

private:
    inline static uint32 id = 0;
};

}  // namespace jupiter
