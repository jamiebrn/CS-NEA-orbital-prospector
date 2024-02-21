#ifndef PLANET_ASTEROID_DROPS_HPP
#define PLANET_ASTEROID_DROPS_HPP

#include <unordered_map>
#include <vector>

#include "Objects/ItemPickupType.hpp"
#include "Renderer/PlanetRenderer.hpp"

static const std::unordered_map<PlanetType, std::vector<std::pair<ItemPickupType, float>>> asteroidDropRates =
{
    {PlanetType::Mercury, {{ItemPickupType::CopperChunk, 0.2}, {ItemPickupType::CopperBar, 0.3}, {ItemPickupType::IronChunk, 0.2}, {ItemPickupType::IronBar, 0.3}}},
    {PlanetType::Venus, {{ItemPickupType::IronChunk, 0.25}, {ItemPickupType::IronBar, 0.35}, {ItemPickupType::TungstenChunk, 0.4}}},
    {PlanetType::Earth, {{ItemPickupType::Rock, 0.3}, {ItemPickupType::CopperChunk, 0.4}, {ItemPickupType::IronChunk, 0.3}}},
    {PlanetType::Moon, {{ItemPickupType::Rock, 0.1}, {ItemPickupType::CopperChunk, 0.5}, {ItemPickupType::IronChunk, 0.4}}},
    {PlanetType::Mars, {{ItemPickupType::Rock, 0.2}, {ItemPickupType::CopperChunk, 0.3}, {ItemPickupType::IronChunk, 0.3}, {ItemPickupType::TungstenChunk, 0.2}}},
    {PlanetType::Jupiter, {{ItemPickupType::CopperChunk, 0.2}, {ItemPickupType::IronChunk, 0.2}, {ItemPickupType::TungstenChunk, 0.3}, {ItemPickupType::AluminiumChunk, 0.3}}},
    {PlanetType::Saturn, {{ItemPickupType::Rock, 0.3}, {ItemPickupType::TungstenChunk, 0.3}, {ItemPickupType::IronChunk, 0.4}}},
    {PlanetType::Uranus, {{ItemPickupType::Rock, 0.3}, {ItemPickupType::CopperChunk, 0.3}, {ItemPickupType::IronChunk, 0.2}}},
    {PlanetType::Neptune, {{ItemPickupType::Rock, 0.3}, {ItemPickupType::CopperChunk, 0.3}, {ItemPickupType::IronChunk, 0.2}}}
};

#endif