// UpgradeManager.hpp

#ifndef UPGRADE_MANAGER_HPP
#define UPGRADE_MANAGER_HPP

// Include libraries
#include <vector>
#include <unordered_map>
#include <json.hpp>

// Include headers
#include "Manager/TextureManager.hpp"
#include "Constants.hpp"

// Enum containing all upgrades
enum class UpgradeType
{
    PrototypeEngine,
    ShipCoolingSystem,
    InterplanetaryEngine,
    InterplanetaryEngine2,
    InterplanetaryEngine3,
    UltimateInterplanetaryEngine,

    SpeedIncrease,
    DamageIncrease,
    HealthIncrease,

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

    // Get the current best engine upgrade
    static UpgradeType getBestEngineUpgrade();

    // Delete all upgrades
    static inline void reset() {upgrades.clear();}

    // Get a reference to the upgrades vector
    static inline const std::vector<UpgradeType>& getUpgrades() {return upgrades;}

    // Get and set functions for player ship upgrade data
    static inline float getSpeedAmount() {return speedAmount;}
    static inline float getDamageAmount() {return damageAmount;}
    static inline int getHealthAmount() {return healthAmount;}
    static inline void setSpeedAmount(float amount) {speedAmount = amount;}
    static inline void setDamageAmount(float amount) {damageAmount = amount;}
    static inline void setHealthAmount(int amount) {healthAmount = amount;}

// Private member variables
private:
    // Vector containing all unlocked upgrades
    static std::vector<UpgradeType> upgrades;

    // Variables storing player ship upgrade data
    static float speedAmount;
    static float damageAmount;
    static int healthAmount;

};

// Map storing the texture types which correspond to the upgrade type
inline const std::unordered_map<UpgradeType, TextureType> upgradeTextureMap =
{
    {UpgradeType::PrototypeEngine, TextureType::PrototypeEngine},
    {UpgradeType::InterplanetaryEngine, TextureType::InterplanetaryEngine},
    {UpgradeType::InterplanetaryEngine2, TextureType::InterplanetaryEngine2},
    {UpgradeType::InterplanetaryEngine3, TextureType::InterplanetaryEngine3},
    {UpgradeType::UltimateInterplanetaryEngine, TextureType::UltimateInterplanetaryEngine},

    {UpgradeType::ShipCoolingSystem, TextureType::ShipCoolingSystem},

    {UpgradeType::SpeedIncrease, TextureType::SpeedIncrease},
    {UpgradeType::DamageIncrease, TextureType::DamageIncrease},
    {UpgradeType::HealthIncrease, TextureType::HealthIncrease}
};

#endif