// InventoryManager.cpp

#include "Manager/InventoryManager.hpp"

// Initialise member variables, as is static class
std::unordered_map<ItemPickupType, int> InventoryManager::itemsCount;
int InventoryManager::silverCoins;
int InventoryManager::currentLevel = 1;
int InventoryManager::levelExp = 0;
int InventoryManager::maxLevelExp = 20;

// Add amount of item to inventory
void InventoryManager::addItem(ItemPickupType type, int amount)
{
    // Initialise item in inventory (if not already)
    initTypeTest(type);

    // Add amount of item to inventory
    itemsCount[type] += amount;
}

// Get amount of item currently held in inventory
int InventoryManager::getItemCount(ItemPickupType type)
{
    // Initialise item in inventory (if not already)
    initTypeTest(type);
    
    // Return amount of item in inventory
    return itemsCount[type];
}

// Sell amount of item
void InventoryManager::sellItems(ItemPickupType type, int count)
{
    // Limit amount to sell to be only amount player actually has stored
    count = std::min(count, getItemCount(type));

    // Add silver coins from selling items, calculated from item price map
    addSilverCoins(itemBasePrice.at(type) * count);

    // Remove items from inventory by adding a negative amount of items
    addItem(type, -count);
}

// Add level experience
void InventoryManager::addExperience(int amount)
{
    // Add amount to level experience
    levelExp += amount;

    // If level experience is over level up threshold, level up
    if (levelExp >= maxLevelExp)
    {
        // Level up
        levelUp();
    }

}

// Level up
void InventoryManager::levelUp()
{
    // Subtract experience amount needed to level up
    levelExp -= maxLevelExp;

    // Add to amount of experience needed to level up
    maxLevelExp += 10 * currentLevel;

    // Increase current level
    currentLevel++;

}

// Reset whole inventory
void InventoryManager::reset()
{

    // For every item in inventory, set count to 0
    for (auto itemPair : itemsCount)
    {
        // Get item type from map
        ItemPickupType type = itemPair.first;

        // Set item count to 0
        itemsCount.at(type) = 0;
    }

    // Reset level stats
    currentLevel = 1;
    levelExp = 0;
    maxLevelExp = 20;

    // Reset silver coins
    resetSilverCoins();

}

// Initialise specific item type in inventory
void InventoryManager::initTypeTest(ItemPickupType type)
{
    // If item does not exist in inventory map, initialise it to 0
    if (itemsCount.count(type) == 0)
    {
        // Initialise to 0
        itemsCount[type] = 0;
    }
}