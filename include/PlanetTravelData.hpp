#ifndef PLANET_TRAVEL_DATA_HPP
#define PLANET_TRAVEL_DATA_HPP

#include <map>

#include "Manager/UpgradeManager.hpp"
#include "Renderer/PlanetRenderer.hpp"

struct PlanetTravelData
{
    PlanetType planetType;
    UpgradeType requiredUpgrade = UpgradeType::NONE;
    PlanetType prerequisitePlanet = PlanetType::NONE;
};

static const std::map<std::string, PlanetTravelData> planetTravelDataMap = {
    {"Moon", {PlanetType::Moon, UpgradeType::PrototypeEngine, PlanetType::Earth}},
    {"Mercury", {PlanetType::Mercury, UpgradeType::ShipCoolingSystem}},
    {"Venus", {PlanetType::Venus, UpgradeType::ShipCoolingSystem}},
    {"Earth", {PlanetType::Earth}},
    {"Mars", {PlanetType::Mars, UpgradeType::InterplanetaryEngine}},
    {"Jupiter", {PlanetType::Jupiter, UpgradeType::InterplanetaryEngine2}},
    {"Saturn", {PlanetType::Saturn, UpgradeType::InterplanetaryEngine2}},
    {"Uranus", {PlanetType::Uranus, UpgradeType::InterplanetaryEngine3}},
    {"Neptune", {PlanetType::Neptune, UpgradeType::UltimateInterplanetaryEngine}}
};

#endif