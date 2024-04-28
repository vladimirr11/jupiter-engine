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

    template <typename CompType, typename... Args>
    void assign(Args&&... args) {}

    template <typename CompType>
    void remove() {}

    const uint32 getId() const { return id; }
    const std::bitset<kMaxComponents> getComponents() const { return components; }

private:
    ECRegistry* registry = nullptr;
    uint32 id{};
    std::bitset<kMaxComponents> components;
};

template <typename Derived>
struct Component {
    using type = Derived;
};

/// @brief Used to retrieve unique component type id
struct ComponentFamily {
public:
    template <typename Type,
              typename = std::enable_if_t<std::is_base_of_v<Component<Type>, Type>, void>>
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

class IComponentPool {
public:
    virtual ~IComponentPool() = default;

    virtual void clear() = 0;
};

template <typename Type>
class ComponentPool final : public IComponentPool {
public:
    ComponentPool() {}

    void add(const Type& comp) {}

    template <typename... Args>
    void add(Args&&... args) {}

    uint64 size() const {}
    void remove(const Entity& entity) {}
    void clear() override {}

private:
    std::vector<Type> pool;
};

class ECRegistry {
public:
private:
    std::vector<UniquePtr<IComponentPool>> pools;
};

}  // namespace jupiter
