// Recipes.hpp

#ifndef RECIPES_HPP
#define RECIPES_HPP

// Include libraries
#include <map>
#include <vector>

// Include headers
#include "Objects/ItemPickupType.hpp"
#include "Manager/UpgradeManager.hpp"

// Namespace recipes, containing all recipe data
namespace Recipes
{

// Struct containing all data related to a smelting recipe
struct SmeltData
{
    ItemPickupType product;
    std::map<ItemPickupType, int> requiredItems;
    int requiredCoins;
};

// Struct containing all data related to an upgrade recipe
struct UpgradeData
{
    std::map<ItemPickupType, int> requiredItems;
    int requiredCoins;

    UpgradeType upgrade;
    UpgradeType prerequisiteUpgrade = UpgradeType::NONE;
};

// Constant map, mapping an item type to its smelting recipe
inline const std::vector<SmeltData> smelting =
{
    {ItemPickupType::CopperBar, {{ItemPickupType::CopperChunk, 2}}, 1},
    {ItemPickupType::IronBar, {{ItemPickupType::IronChunk, 3}}, 2},
    {ItemPickupType::CopronBar, {{ItemPickupType::CopperBar, 1}, {ItemPickupType::IronBar, 1}}, 5},
    {ItemPickupType::TungstenBar, {{ItemPickupType::TungstenChunk, 3}}, 6},
    {ItemPickupType::AluminiumBar, {{ItemPickupType::AluminiumChunk, 2}}, 9}
};

// Constant vector, containing all upgrade recipe data
inline const std::vector<UpgradeData> upgrades =
{
    {{{ItemPickupType::CopperBar, 3}, {ItemPickupType::IronBar, 2}}, 30, UpgradeType::PrototypeEngine},
    {{{ItemPickupType::CopperBar, 5}, {ItemPickupType::IronBar, 3}}, 50, UpgradeType::InterplanetaryEngine, UpgradeType::PrototypeEngine},
    {{{ItemPickupType::CopronBar, 3}, {ItemPickupType::TungstenBar, 2}}, 85, UpgradeType::InterplanetaryEngine2, UpgradeType::InterplanetaryEngine},
    {{{ItemPickupType::TungstenBar, 4}, {ItemPickupType::AluminiumBar, 3}}, 110, UpgradeType::InterplanetaryEngine3, UpgradeType::InterplanetaryEngine2},
    {{{ItemPickupType::TungstenBar, 6}, {ItemPickupType::AluminiumBar, 5}, {ItemPickupType::CopronBar, 4}}, 150, UpgradeType::UltimateInterplanetaryEngine, UpgradeType::InterplanetaryEngine3},

    {{{ItemPickupType::CopperBar, 7}, {ItemPickupType::IronBar, 5}}, 70, UpgradeType::ShipCoolingSystem},

    {{{ItemPickupType::CopperBar, 5}, {ItemPickupType::IronBar, 2}}, 40, UpgradeType::SpeedIncrease},
    {{{ItemPickupType::IronBar, 4}, {ItemPickupType::TungstenBar, 2}}, 50, UpgradeType::DamageIncrease},
    {{{ItemPickupType::CopperBar, 3}, {ItemPickupType::CopperBar, 2}}, 45, UpgradeType::HealthIncrease}
};

}

#endif