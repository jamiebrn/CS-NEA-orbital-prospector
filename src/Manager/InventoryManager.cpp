#include "Manager/InventoryManager.hpp"

std::unordered_map<ItemPickupType, int> InventoryManager::itemsCount;
int InventoryManager::silverCoins;
int InventoryManager::currentLevel = 1;
int InventoryManager::levelExp = 0;
int InventoryManager::maxLevelExp = 20;

void InventoryManager::addItem(ItemPickupType type, int amount)
{
    initTypeTest(type);

    itemsCount[type] += amount;

    addExperience(itemBasePrice.at(type) * amount);
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

void InventoryManager::addExperience(int amount)
{

    levelExp += amount;
    if (levelExp >= maxLevelExp)
    {
        levelUp();
    }

}

void InventoryManager::levelUp()
{

    levelExp -= maxLevelExp;
    maxLevelExp += 10 * currentLevel;
    currentLevel++;

}

void InventoryManager::reset()
{

    for (auto itemPair : itemsCount)
    {
        ItemPickupType type = itemPair.first;
        itemsCount.at(type) = 0;
    }

    currentLevel = 1;
    levelExp = 0;
    maxLevelExp = 20;

    resetSilverCoins();

}

void InventoryManager::initTypeTest(ItemPickupType type)
{
    if (itemsCount.count(type) == 0)
    {
        itemsCount[type] = 0;
    }
}