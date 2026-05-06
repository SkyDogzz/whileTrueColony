#pragma once

#include <array>
#include <cstddef>
#include <optional>
#include <string_view>
#include <vector>

enum class ResourceType {
    None,
    Wood,
    Stone,
    IronOre,
    IronPlate,
    CopperOre,
    CopperWire,
    Coal,
    Water,
    EnergyCell,
    Circuit,
    Crystal,
    Count
};

enum class InventoryOwnerType { Robot, Storage, Base, Building, Unknown };

enum class InventoryTransferResult {
    Success,
    InvalidResource,
    InvalidAmount,
    NotEnoughSource,
    NotEnoughCapacity,
    SameInventory
};

using ResourceAmount = int;
using InventoryId = unsigned int;
using EntityId = unsigned int;

constexpr std::size_t ResourceTypeCount = static_cast<std::size_t>(ResourceType::Count);

struct ResourceStack {
    ResourceType type = ResourceType::None;
    ResourceAmount amount = 0;
};

struct ResourceDefinition {
    ResourceType type = ResourceType::None;
    std::string_view id;
    std::string_view displayName;
    ResourceAmount defaultStackLimit = 0;
    bool storable = true;
};

struct InventoryOwner {
    InventoryOwnerType type = InventoryOwnerType::Unknown;
    EntityId entityId = 0;
};

struct InventoryCapacity {
    ResourceAmount total = 0;
    std::array<ResourceAmount, ResourceTypeCount> perResource { };
};

struct InventoryReservation {
    InventoryId id = 0;
    ResourceType type = ResourceType::None;
    ResourceAmount amount = 0;
};

struct InventoryTransferRequest {
    ResourceType type = ResourceType::None;
    ResourceAmount amount = 0;
    bool allowPartial = false;
};

struct InventoryTransferReport {
    InventoryTransferResult result = InventoryTransferResult::Success;
    ResourceType type = ResourceType::None;
    ResourceAmount requested = 0;
    ResourceAmount moved = 0;
};

class Inventory {
public:
    Inventory() = default;
    explicit Inventory(ResourceAmount totalCapacity);
    Inventory(ResourceAmount totalCapacity, InventoryOwner owner);

    void setOwner(InventoryOwner newOwner);
    [[nodiscard]] InventoryOwner getOwner() const;
    [[nodiscard]] InventoryOwnerType getOwnerType() const;
    [[nodiscard]] EntityId getOwnerId() const;

    void setTotalCapacity(ResourceAmount newCapacity);
    [[nodiscard]] ResourceAmount getTotalCapacity() const;
    [[nodiscard]] ResourceAmount getUsedCapacity() const;
    [[nodiscard]] ResourceAmount getFreeCapacity() const;
    [[nodiscard]] bool isFull() const;
    [[nodiscard]] bool isEmpty() const;

    void setResourceCapacity(ResourceType type, ResourceAmount newCapacity);
    [[nodiscard]] ResourceAmount getResourceCapacity(ResourceType type) const;
    [[nodiscard]] ResourceAmount getResourceFreeCapacity(ResourceType type) const;

    [[nodiscard]] ResourceAmount get(ResourceType type) const;
    [[nodiscard]] ResourceAmount getReserved(ResourceType type) const;
    [[nodiscard]] ResourceAmount getAvailable(ResourceType type) const;
    [[nodiscard]] bool has(ResourceType type, ResourceAmount amount) const;
    [[nodiscard]] bool canAdd(ResourceType type, ResourceAmount amount) const;
    [[nodiscard]] bool canRemove(ResourceType type, ResourceAmount amount) const;

    [[nodiscard]] ResourceAmount add(ResourceType type, ResourceAmount amount);
    [[nodiscard]] ResourceAmount remove(ResourceType type, ResourceAmount amount);
    void clear();
    void clear(ResourceType type);

    [[nodiscard]] std::optional<InventoryReservation> reserve(ResourceType type, ResourceAmount amount);
    [[nodiscard]] bool consumeReservation(const InventoryReservation& reservation);
    [[nodiscard]] bool cancelReservation(const InventoryReservation& reservation);
    void clearReservations();

    [[nodiscard]] InventoryTransferReport transferTo(Inventory& destination, const InventoryTransferRequest& request);
    [[nodiscard]] InventoryTransferReport transferFrom(Inventory& source, const InventoryTransferRequest& request);

    [[nodiscard]] std::vector<ResourceStack> stacks() const;
    [[nodiscard]] std::vector<ResourceStack> nonEmptyStacks() const;

    [[nodiscard]] static bool isValidResource(ResourceType type);
    [[nodiscard]] static std::string_view resourceId(ResourceType type);
    [[nodiscard]] static std::string_view resourceDisplayName(ResourceType type);
    [[nodiscard]] static const std::array<ResourceDefinition, ResourceTypeCount>& resourceDefinitions();

private:
    std::array<ResourceAmount, ResourceTypeCount> amounts { };
    std::array<ResourceAmount, ResourceTypeCount> reserved { };
    std::vector<InventoryReservation> reservations;
    InventoryCapacity capacity { };
    InventoryOwner owner { };
    InventoryId nextReservationId = 1;
};
