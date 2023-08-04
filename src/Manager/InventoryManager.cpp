#include "Manager/InventoryManager.hpp"

std::unordered_map<ItemPickupType, int> InventoryManager::itemsCount;

void InventoryManager::addItem(ItemPickupType type, int amount)
{
    initTypeTest(type);

    itemsCount[type] += amount;
}

int InventoryManager::getItemCount(ItemPickupType type)
{
    initTypeTest(type);
    
    return itemsCount[type];
}

void InventoryManager::initTypeTest(ItemPickupType type)
{
    if (itemsCount.count(type) == 0)
    {
        itemsCount[type] = 0;
    }
}