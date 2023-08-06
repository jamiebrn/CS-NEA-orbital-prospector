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

    inline static void resetSilverCoins() {silverCoins = 0;}

    inline static void addSilverCoins(int amount) {silverCoins += amount;}

    inline static int getSilverCoins() {return silverCoins;}

private:
    static void initTypeTest(ItemPickupType type);

private:
    static std::unordered_map<ItemPickupType, int> itemsCount;

    static int silverCoins;

};

#endif