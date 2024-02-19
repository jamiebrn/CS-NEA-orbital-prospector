#ifndef ITEM_PICKUP_TYPE_HPP
#define ITEM_PICKUP_TYPE_HPP

#include <map>
#include <json.hpp>

#include "Manager/TextureManager.hpp"

#define DECLARE_ITEM_PICKUP_TYPE_ENUM \
    X(Rock) \
    X(CopperChunk) \
    X(IronChunk) \
    X(CopperBar) \
    X(IronBar) \
    X(CopronBar) \
    X(NONE)

enum ItemPickupType
{
#define X(item) item,
    DECLARE_ITEM_PICKUP_TYPE_ENUM
#undef X
};

NLOHMANN_JSON_SERIALIZE_ENUM(ItemPickupType, 
{
#define X(item) {ItemPickupType::item, #item},
    DECLARE_ITEM_PICKUP_TYPE_ENUM
#undef X
})

std::string itemPickupTypeToString(ItemPickupType type)
{
    switch (type)
    {
    #define X(item) case ItemPickupType::item: return #item;
        DECLARE_ITEM_PICKUP_TYPE_ENUM
    #undef X
    }
}

ItemPickupType stringToItemPickupType(std::string string)
{
    #define X(item) if (string == #item) return ItemPickupType::item;
        DECLARE_ITEM_PICKUP_TYPE_ENUM
    #undef X
}

/*
const std::map<ItemPickupType, const char*> itemPickupToStringMap =
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
*/

#endif