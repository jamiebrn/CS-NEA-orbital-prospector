// ItemPickupType.hpp

#ifndef ITEM_PICKUP_TYPE_HPP
#define ITEM_PICKUP_TYPE_HPP

// Include libraries
#include <map>
#include <json.hpp>

// Include headers
#include "Manager/TextureManager.hpp"

// Enum containing all possible items types
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

// Constant hash map, which maps each item pickup type to its corresponding texture
const std::map<ItemPickupType, TextureType> itemTextureMap = {
    {ItemPickupType::Rock, TextureType::PickupRock},
    {ItemPickupType::CopperChunk, TextureType::PickupCopperChunk},
    {ItemPickupType::IronChunk, TextureType::PickupIronChunk},
    {ItemPickupType::CopperBar, TextureType::CopperBar},
    {ItemPickupType::IronBar, TextureType::IronBar},
    {ItemPickupType::CopronBar, TextureType::CopronBar},
    {ItemPickupType::TungstenChunk, TextureType::TungstenChunk},
    {ItemPickupType::TungstenBar, TextureType::TungstenBar},
    {ItemPickupType::AluminiumChunk, TextureType::AluminiumChunk},
    {ItemPickupType::AluminiumBar, TextureType::AluminiumBar}
};

#endif