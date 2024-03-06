// UpgradeManager.cpp

#include "Manager/UpgradeManager.hpp"

// Initialise member variables, as is static class
std::vector<UpgradeType> UpgradeManager::upgrades;
float UpgradeManager::speedAmount = 1.0f;
float UpgradeManager::damageAmount = 1.0f;
int UpgradeManager::healthAmount = STARTING_MAX_HEALTH;

// Return whether a specific upgrade has been unlocked
bool UpgradeManager::hasUpgrade(UpgradeType upgrade)
{
    // If the upgrade type passed in is none, return true by default
    if (upgrade == UpgradeType::NONE)
        return true;
    
    // Iterate through all upgrades unlocked and test if the upgrade passed in matches
    for (UpgradeType type : upgrades)
    {
        // If upgrade passed in exists in the vector, return true
        if (type == upgrade) return true;
    }

    // Return false if upgrade is not found
    return false;
}

// Unlock a specific upgrade
void UpgradeManager::unlockUpgrade(UpgradeType upgrade)
{
    switch (upgrade)
    {
        // Add to speed modifier if speed increase upgrade
        case UpgradeType::SpeedIncrease:
            speedAmount += 0.1f;
            break;
        // Add to damage modifier if damage increase upgrade
        case UpgradeType::DamageIncrease:
            damageAmount += 0.5f;
            break;
        // Add to health value if health increase upgrade
        case UpgradeType::HealthIncrease:
            healthAmount += 5;
            break;
        // Any other upgrade is added to upgrade vector
        default:
            // Add upgrade to unlocked upgrades vector
            upgrades.push_back(upgrade);
            break;
    }
}

// Get the current best engine upgrade
UpgradeType UpgradeManager::getBestEngineUpgrade()
{
    // Slightly messy code, but only a few cases so not worth making a separate system for
    // Implementation such as using an array with descending order of engine "value" and iterating over it would use more memory and is less readable
    if (hasUpgrade(UpgradeType::UltimateInterplanetaryEngine)) return UpgradeType::UltimateInterplanetaryEngine;
    if (hasUpgrade(UpgradeType::InterplanetaryEngine3)) return UpgradeType::InterplanetaryEngine3;
    if (hasUpgrade(UpgradeType::InterplanetaryEngine2)) return UpgradeType::InterplanetaryEngine2;
    if (hasUpgrade(UpgradeType::InterplanetaryEngine)) return UpgradeType::InterplanetaryEngine;
    if (hasUpgrade(UpgradeType::PrototypeEngine)) return UpgradeType::PrototypeEngine;
 
    // When no engine upgrade has been unlocked
    return UpgradeType::NONE;
}