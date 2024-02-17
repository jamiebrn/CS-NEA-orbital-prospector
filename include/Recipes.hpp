#ifndef RECIPES_HPP
#define RECIPES_HPP

#include <map>
#include <vector>

#include "Objects/ItemPickupType.hpp"

namespace Recipes
{

struct SmeltData
{
    ItemPickupType product;
    std::map<ItemPickupType, int> requiredItems;
    int requiredCoins;
};

inline const std::vector<SmeltData> smelting =
{
    {ItemPickupType::CopperBar, {{ItemPickupType::CopperChunk, 2}}, 1},
    {ItemPickupType::IronBar, {{ItemPickupType::IronChunk, 3}}, 2}
};

}

#endif