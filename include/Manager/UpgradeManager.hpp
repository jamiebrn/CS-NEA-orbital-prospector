// UpgradeManager.hpp

#ifndef UPGRADE_MANAGER_HPP
#define UPGRADE_MANAGER_HPP

// Include libraries
#include <vector>
#include <unordered_map>
#include <json.hpp>

// Include headers
#include "Manager/TextureManager.hpp"

// Enum containing all upgrades
enum class UpgradeType
{
    PrototypeEngine,
    ShipCoolingSystem,
    InterplanetaryEngine,
    InterplanetaryEngine2,
    InterplanetaryEngine3,
    UltimateInterplanetaryEngine,

    NONE
};

// Declare upgrade manager class
class UpgradeManager
{

// Delete constructor as is static class
private:
    UpgradeManager() = delete;

// Public class functions
public:
    // Return whether a specific upgrade has been unlocked
    static bool hasUpgrade(UpgradeType upgrade);

    // Unlock a specific upgrade
    static void unlockUpgrade(UpgradeType upgrade);

    // Delete all upgrades
    static inline void reset() {upgrades.clear();}

    // Get a reference to the upgrades vector
    static inline const std::vector<UpgradeType>& getUpgrades() {return upgrades;}

// Private member variables
private:
    // Vector containing all unlocked upgrades
    static std::vector<UpgradeType> upgrades;

};

// Map storing the texture types which correspond to the upgrade type
inline const std::unordered_map<UpgradeType, TextureType> upgradeTextureMap =
{
    {UpgradeType::PrototypeEngine, TextureType::PrototypeEngine},
    {UpgradeType::InterplanetaryEngine, TextureType::InterplanetaryEngine},
    {UpgradeType::InterplanetaryEngine2, TextureType::InterplanetaryEngine2},
    {UpgradeType::InterplanetaryEngine3, TextureType::InterplanetaryEngine3},
    {UpgradeType::UltimateInterplanetaryEngine, TextureType::UltimateInterplanetaryEngine},

    {UpgradeType::ShipCoolingSystem, TextureType::ShipCoolingSystem}
};

#endif