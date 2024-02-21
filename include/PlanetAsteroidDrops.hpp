#ifndef PLANET_ASTEROID_DROPS_HPP
#define PLANET_ASTEROID_DROPS_HPP

#include <unordered_map>
#include <vector>

#include "Objects/ItemPickupType.hpp"
#include "Renderer/PlanetRenderer.hpp"

static const std::unordered_map<PlanetType, std::vector<std::pair<ItemPickupType, float>>> asteroidDropRates =
{
    {PlanetType::Mercury, {{ItemPickupType::CopperBar, 0.6}, {ItemPickupType::IronBar, 0.4}}},
    {PlanetType::Venus, {{ItemPickupType::Rock, 0.3}, {ItemPickupType::CopperChunk, 0.3}, {ItemPickupType::IronChunk, 0.2}}},
    {PlanetType::Earth, {{ItemPickupType::Rock, 0.3}, {ItemPickupType::CopperChunk, 0.3}, {ItemPickupType::IronChunk, 0.2}}},
    {PlanetType::Moon, {{ItemPickupType::Rock, 0.3}, {ItemPickupType::CopperChunk, 0.3}, {ItemPickupType::IronChunk, 0.2}}},
    {PlanetType::Mars, {{ItemPickupType::Rock, 0.3}, {ItemPickupType::CopperChunk, 0.3}, {ItemPickupType::IronChunk, 0.2}}},
    {PlanetType::Jupiter, {{ItemPickupType::Rock, 0.3}, {ItemPickupType::CopperChunk, 0.3}, {ItemPickupType::IronChunk, 0.2}}},
    {PlanetType::Saturn, {{ItemPickupType::Rock, 0.3}, {ItemPickupType::CopperChunk, 0.3}, {ItemPickupType::IronChunk, 0.2}}},
    {PlanetType::Uranus, {{ItemPickupType::Rock, 0.3}, {ItemPickupType::CopperChunk, 0.3}, {ItemPickupType::IronChunk, 0.2}}},
    {PlanetType::Neptune, {{ItemPickupType::Rock, 0.3}, {ItemPickupType::CopperChunk, 0.3}, {ItemPickupType::IronChunk, 0.2}}}
};

#endif