#ifndef ITEM_PICKUP_TYPE_HPP
#define ITEM_PICKUP_TYPE_HPP

#include <map>
#include <json.hpp>

#include "Manager/TextureManager.hpp"

enum ItemPickupType
{
    Rock,
    CopperChunk,
    IronChunk,

    CopperBar,
    IronBar,
    CopronBar,

    NONE
};

NLOHMANN_JSON_SERIALIZE_ENUM(ItemPickupType, 
{
    {Rock, "rock"},
    {CopperChunk, "copper"},
    {IronChunk, "iron"},
    {CopperBar, "copperbar"},
    {IronBar, "ironbar"},
    {CopronBar, "copronbar"}
})

const std::map<ItemPickupType, std::string> itemPickupToStringMap =
{
    {ItemPickupType::Rock, "rock"},
    {ItemPickupType::CopperChunk, "copper"},
    {ItemPickupType::IronChunk, "iron"},
    {ItemPickupType::CopperBar, "copperbar"},
    {ItemPickupType::IronBar, "ironbar"},
    {ItemPickupType::CopronBar, "copronbar"}
};



const std::map<ItemPickupType, TextureType> itemTextureMap = {
    {ItemPickupType::Rock, TextureType::PickupRock},
    {ItemPickupType::CopperChunk, TextureType::PickupCopperChunk},
    {ItemPickupType::IronChunk, TextureType::PickupIronChunk},
    {ItemPickupType::CopperBar, TextureType::CopperBar},
    {ItemPickupType::IronBar, TextureType::IronBar},
    {ItemPickupType::CopronBar, TextureType::CopronBar}
};

#endif