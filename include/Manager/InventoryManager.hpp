#ifndef INVENTORY_MANAGER_HPP
#define INVENTORY_MANAGER_HPP

#include <unordered_map>

#include "Objects/ItemPickupType.hpp"

class InventoryManager
{

private:
    InventoryManager() = delete;

public:

    static void addItem(ItemPickupType type, int amount);

    static int getItemCount(ItemPickupType type);

    static void sellItems(ItemPickupType type, int count);

    static void reset();

    inline static void resetSilverCoins() {silverCoins = 0;}

    inline static void addSilverCoins(int amount) {silverCoins += amount;}

    inline static int getSilverCoins() {return silverCoins;}

    static void addExperience(int amount);

    inline static int getCurrentLevel() {return currentLevel;}

    inline static int getLevelExp() {return levelExp;}

    inline static int getMaxLevelExp() {return maxLevelExp;}

private:
    static void initTypeTest(ItemPickupType type);

    static void levelUp();

private:
    static std::unordered_map<ItemPickupType, int> itemsCount;

    inline static const std::unordered_map<ItemPickupType, int> itemBasePrice = {
        {ItemPickupType::Rock, 2},
        {ItemPickupType::CopperChunk, 4},
        {ItemPickupType::IronChunk, 5}
    };

    static int silverCoins;

    static int currentLevel;
    static int levelExp;
    static int maxLevelExp;

};

#endif