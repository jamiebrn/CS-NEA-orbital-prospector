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
    UpgradeType prerequisiteUpgrade = UpgradeType::NONE;
};

inline const std::vector<SmeltData> smelting =
{
    {ItemPickupType::CopperBar, {{ItemPickupType::CopperChunk, 2}}, 1},
    {ItemPickupType::IronBar, {{ItemPickupType::IronChunk, 3}}, 2},
    {ItemPickupType::CopronBar, {{ItemPickupType::CopperBar, 1}, {ItemPickupType::IronBar, 1}}, 5},
    {ItemPickupType::TungstenBar, {{ItemPickupType::TungstenChunk, 3}}, 6},
    {ItemPickupType::AluminiumBar, {{ItemPickupType::AluminiumChunk, 2}}, 9}    
};

inline const std::vector<UpgradeData> upgrades =
{
    {{{ItemPickupType::CopperBar, 9}, {ItemPickupType::IronBar, 6}}, 60, UpgradeType::PrototypeEngine},
    {{{ItemPickupType::CopronBar, 13}, {ItemPickupType::IronBar, 5}}, 150, UpgradeType::InterplanetaryEngine, UpgradeType::PrototypeEngine},
    {{{ItemPickupType::CopperBar, 1}, {ItemPickupType::IronBar, 1}}, 10, UpgradeType::InterplanetaryEngine2, UpgradeType::InterplanetaryEngine},
    {{{ItemPickupType::CopperBar, 1}, {ItemPickupType::IronBar, 1}}, 10, UpgradeType::InterplanetaryEngine3, UpgradeType::InterplanetaryEngine2},
    {{{ItemPickupType::CopperBar, 1}, {ItemPickupType::IronBar, 1}}, 10, UpgradeType::UltimateInterplanetaryEngine, UpgradeType::InterplanetaryEngine3},

    {{{ItemPickupType::CopperBar, 1}, {ItemPickupType::IronBar, 1}}, 10, UpgradeType::ShipCoolingSystem}
};

}

#endif