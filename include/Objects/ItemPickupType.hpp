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
    TungstenChunk,
    TungstenBar,
    AluminiumChunk,
    AluminiumBar,

    NONE
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