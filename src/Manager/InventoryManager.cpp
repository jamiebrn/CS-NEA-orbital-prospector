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

// Halves the player's inventory, used for when the player dies
void InventoryManager::halfInventoryAmount()
{
    // Iterate over all inventory items and subtract half of item amount
    for (auto itemPair : itemsCount)
    {
        // Get amount of item
        int amount = itemPair.second;
        // Calculate half of amount of item, rounding up
        int halfAmount = static_cast<int>(std::ceil(static_cast<float>(amount) / 2.0f));
        // Subtract half amount from inventory
        itemsCount[itemPair.first] = std::max(itemsCount[itemPair.first] - halfAmount, 0);
    }

    // Calculate half of player's coins and subtract
    silverCoins = std::max(silverCoins - static_cast<int>(std::ceil(static_cast<float>(silverCoins) / 2.0f)), 0);
}

// Returns two integers, representing half of the amount of items in the player's inventory,
// the other representing half of the player's coins.
std::pair<int, int> InventoryManager::getHalfInventoryAmount()
{
    // Create pair object storing count of half of inventory
    std::pair<int, int> inventoryHalfAmount;

    // Initialise first value (storing half amount of items) to 0
    inventoryHalfAmount.first = 0;

    // Iterate over all inventory items and add half of amount
    for (auto itemPair : itemsCount)
    {
        // Get amount of item
        int amount = itemPair.second;
        // Calculate half of amount of item, rounding up
        int halfAmount = static_cast<int>(std::ceil(static_cast<float>(amount) / 2.0f));
        // Add half amount to pair object
        inventoryHalfAmount.first += halfAmount;
    }

    // Calculate half of player's coins and store in pair object
    inventoryHalfAmount.second = static_cast<int>(std::ceil(static_cast<float>(silverCoins) / 2.0f));

    // Return pair object storing half of inventory amount
    return inventoryHalfAmount;
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