#include "Manager/InventoryManager.hpp"

std::unordered_map<ItemPickupType, int> InventoryManager::itemsCount;
int InventoryManager::silverCoins;

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

void InventoryManager::sellItems(ItemPickupType type, int count)
{
    count = std::min(count, getItemCount(type));

    addSilverCoins(itemBasePrice.at(type) * count);

    addItem(type, -count);
}

void InventoryManager::reset()
{

    for (auto itemPair : itemsCount)
    {
        ItemPickupType type = itemPair.first;
        itemsCount.at(type) = 0;
    }

    resetSilverCoins();

}

void InventoryManager::initTypeTest(ItemPickupType type)
{
    if (itemsCount.count(type) == 0)
    {
        itemsCount[type] = 0;
    }
}