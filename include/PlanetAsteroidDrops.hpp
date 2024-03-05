// PlanetAsteroidDrops.hpp

#ifndef PLANET_ASTEROID_DROPS_HPP
#define PLANET_ASTEROID_DROPS_HPP

// Include libraries
#include <unordered_map>
#include <vector>

// Include headers
#include "Objects/ItemPickupType.hpp"
#include "Renderer/PlanetRenderer.hpp"

// Constant map containing each planet type, mapped to a vector containing all possible asteroid item drops and their probabilities
static const std::unordered_map<PlanetType, std::vector<std::pair<ItemPickupType, float>>> asteroidDropRates =
{
    {PlanetType::Mercury, {{ItemPickupType::CopperChunk, 0.2}, {ItemPickupType::CopperBar, 0.3}, {ItemPickupType::IronChunk, 0.2}, {ItemPickupType::IronBar, 0.3}}},
    {PlanetType::Venus, {{ItemPickupType::IronChunk, 0.25}, {ItemPickupType::IronBar, 0.35}, {ItemPickupType::TungstenChunk, 0.4}}},
    {PlanetType::Earth, {{ItemPickupType::Rock, 0.3}, {ItemPickupType::CopperChunk, 0.4}, {ItemPickupType::IronChunk, 0.3}}},
    {PlanetType::Moon, {{ItemPickupType::Rock, 0.1}, {ItemPickupType::CopperChunk, 0.5}, {ItemPickupType::IronChunk, 0.4}}},
    {PlanetType::Mars, {{ItemPickupType::Rock, 0.2}, {ItemPickupType::CopperChunk, 0.3}, {ItemPickupType::IronChunk, 0.3}, {ItemPickupType::TungstenChunk, 0.2}}},
    {PlanetType::Jupiter, {{ItemPickupType::CopperChunk, 0.2}, {ItemPickupType::IronChunk, 0.2}, {ItemPickupType::TungstenChunk, 0.3}, {ItemPickupType::AluminiumChunk, 0.3}}},
    {PlanetType::Saturn, {{ItemPickupType::Rock, 0.3}, {ItemPickupType::TungstenChunk, 0.3}, {ItemPickupType::IronChunk, 0.4}}},
    {PlanetType::Uranus, {{ItemPickupType::Rock, 0.2}, {ItemPickupType::TungstenChunk, 0.4}, {ItemPickupType::AluminiumChunk, 0.4}}},
    {PlanetType::Neptune, {{ItemPickupType::TungstenChunk, 0.5}, {ItemPickupType::AluminiumChunk, 0.5}}}
};

#endif