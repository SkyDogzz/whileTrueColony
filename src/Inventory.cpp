#include "Inventory.hpp"

Inventory::Inventory(ResourceAmount totalCapacity)
    : capacity(totalCapacity)
{
}
Inventory::Inventory(ResourceAmount totalCapacity, InventoryOwner owner)
    : capacity(totalCapacity)
    , owner(owner)
{
}

void Inventory::setOwner(InventoryOwner newOwner)
{
    if (newOwner.type == InventoryOwnerType::Unknown)
        return;
    owner = newOwner;
}

InventoryOwner Inventory::getOwner() const { return owner; }

InventoryOwnerType Inventory::getOwnerType() const { return owner.type; }

EntityId Inventory::getOwnerId() const { return owner.entityId; }

void Inventory::setTotalCapacity(ResourceAmount newCapacity)
{
    if (newCapacity <= 0)
        capacity.total = 0;
    else
        capacity.total = newCapacity;
}
