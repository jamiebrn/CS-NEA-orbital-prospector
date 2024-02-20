#ifndef RECIPES_HPP
#define RECIPES_HPP

#include <map>
#include <vector>

#include "Objects/ItemPickupType.hpp"
#include "Manager/UpgradeManager.hpp"

namespace Recipes
{

struct SmeltData
{
    ItemPickupType product;
    std::map<ItemPickupType, int> requiredItems;
    int requiredCoins;
};

struct UpgradeData
{
    std::map<ItemPickupType, int> requiredItems;
    int requiredCoins;

    UpgradeType upgrade;
};

inline const std::vector<SmeltData> smelting =
{
    {ItemPickupType::CopperBar, {{ItemPickupType::CopperChunk, 2}}, 1},
    {ItemPickupType::IronBar, {{ItemPickupType::IronChunk, 3}}, 2},
    {ItemPickupType::CopronBar, {{ItemPickupType::CopperBar, 1}, {ItemPickupType::IronBar, 1}}, 5}
};

inline const std::vector<UpgradeData> upgrades =
{
    {{{ItemPickupType::CopperBar, 1}, {ItemPickupType::IronBar, 1}}, 10, UpgradeType::PrototypeEngine}
};

}

#endif