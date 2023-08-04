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

private:
    static void initTypeTest(ItemPickupType type);

private:
    static std::unordered_map<ItemPickupType, int> itemsCount;

};

#endif