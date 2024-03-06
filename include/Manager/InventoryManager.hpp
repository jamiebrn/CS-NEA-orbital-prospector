// InventoryManager.hpp

#ifndef INVENTORY_MANAGER_HPP
#define INVENTORY_MANAGER_HPP

// Include libraries
#include <unordered_map>
#include <iostream>

// Include headers
#include "Objects/ItemPickupType.hpp"

// Declare inventory manager class
class InventoryManager
{

// Delete constructor, as is static class
private:
    InventoryManager() = delete;

// Public class functions
public:
    // Add item and amount to inventory
    static void addItem(ItemPickupType type, int amount);

    // Get amount of specific item in inventory
    static int getItemCount(ItemPickupType type);

    // Sell amount of specific item in inventory
    static void sellItems(ItemPickupType type, int count);

    // Reset whole inventory, to contain nothing
    static void reset();

    // Halves the player's inventory, used for when the player dies
    static void halfInventoryAmount();

    // Returns two integers, representing half of the amount of items in the player's inventory,
    // the other representing half of the player's coins.
    static std::pair<int, int> getHalfInventoryAmount();

    // Reset silver coins
    inline static void resetSilverCoins() {silverCoins = 0;}

    // Add amount of silver coins
    inline static void addSilverCoins(int amount) {silverCoins += amount;}

    // Get amount of silver coins
    inline static int getSilverCoins() {return silverCoins;}

    // Add amount of experience
    static void addExperience(int amount);

    // Get current level
    inline static int getCurrentLevel() {return currentLevel;}

    // Get experience on current level
    inline static int getLevelExp() {return levelExp;}

    // Get experience required to level up on current level
    inline static int getMaxLevelExp() {return maxLevelExp;}

    // Override the current level with a new value
    inline static void setCurrentLevel(int level) {currentLevel = level;}

    // Override the current level experience with a new value
    inline static void setLevelExp(int exp) {levelExp = exp;}

    // Override the required level up experience with a new value
    inline static void setMaxLevelExp(int exp) {maxLevelExp = exp;}

    // Get price of a specific item
    inline static int itemPrice(ItemPickupType type) {return itemBasePrice.at(type);}

// Private class functions
private:
    // Initialise item type in inventory
    static void initTypeTest(ItemPickupType type);

    // Level up
    static void levelUp();

// Private member variables
private:
    // Map storing actual inventory data
    // Uses item type as key, with value storing amount of that item stored
    static std::unordered_map<ItemPickupType, int> itemsCount;

    // Constant map storing prices of all items
    inline static const std::unordered_map<ItemPickupType, int> itemBasePrice = {
        {ItemPickupType::Rock, 2},
        {ItemPickupType::CopperChunk, 4},
        {ItemPickupType::IronChunk, 5},
        {ItemPickupType::CopperBar, 12},
        {ItemPickupType::IronBar, 20},
        {ItemPickupType::CopronBar, 45},
        {ItemPickupType::TungstenChunk, 9},
        {ItemPickupType::TungstenBar, 20},
        {ItemPickupType::AluminiumChunk, 11},
        {ItemPickupType::AluminiumBar, 25}
    };

    // Variable storing amount of silver coins held
    static int silverCoins;

    // Variable storing current level
    static int currentLevel;

    // Variable storing current level experience
    static int levelExp;

    // Variable storing experience required to level up
    static int maxLevelExp;

};

#endif