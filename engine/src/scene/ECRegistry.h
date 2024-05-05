#pragma once

// C++ system includes
#include <bitset>
#include <type_traits>
#include <deque>
#include <unordered_map>

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

    template <typename CompType>
    bool hasComponent() {}

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

    uint64 size() const { return pool.size(); }
    void remove(const Entity& entity) {}
    void clear() override {}

private:
    std::vector<Type> pool;
};

class ECRegistry {
public:
    ECRegistry() {}

    Entity& create() {
        // Use this simple approach for now
        static uint32 entityId = 0;
        Entity newEntity{entityId++, this};
        auto entityIdx = freeSlots.empty() ? entities.size() : freeSlots.front();
        if (!freeSlots.empty()) {
            freeSlots.pop_front();
            entities[entityIdx] = newEntity;
        } else {
            entities.push_back(newEntity);
        }
        mapper[entityId - 1] = entityIdx;
        return entities[entityIdx];
    }

private:
    std::vector<UniquePtr<IComponentPool>> pools;
    std::vector<Entity> entities;
    std::deque<size_t> freeSlots;
    std::unordered_map<uint32, size_t> mapper;
};

}  // namespace jupiter
