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

    NONE
};

NLOHMANN_JSON_SERIALIZE_ENUM(ItemPickupType, {
    {Rock, "rock"},
    {CopperChunk, "copper"},
    {IronChunk, "iron"}
})

const std::map<ItemPickupType, TextureType> itemTextureMap = {
    {ItemPickupType::Rock, TextureType::PickupRock},
    {ItemPickupType::CopperChunk, TextureType::PickupCopperChunk},
    {ItemPickupType::IronChunk, TextureType::PickupIronChunk},
    {ItemPickupType::CopperBar, TextureType::CopperBar}
};

#endif