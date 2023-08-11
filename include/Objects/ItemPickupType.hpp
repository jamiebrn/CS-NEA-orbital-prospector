#ifndef ITEM_PICKUP_TYPE_HPP
#define ITEM_PICKUP_TYPE_HPP

#include <unordered_map>

#include "Manager/TextureManager.hpp"

enum class ItemPickupType
{
    Rock,
    CopperChunk,
    IronChunk
};

const std::unordered_map<ItemPickupType, TextureType> itemTextureMap = {
    {ItemPickupType::Rock, TextureType::PickupRock},
    {ItemPickupType::CopperChunk, TextureType::PickupCopperChunk},
    {ItemPickupType::IronChunk, TextureType::PickupIronChunk}
};

#endif