// UpgradeManager.cpp

#include "Manager/UpgradeManager.hpp"

// Initialise member variables, as is static class
std::vector<UpgradeType> UpgradeManager::upgrades;

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
    // Add upgrade to unlocked upgrades vector
    upgrades.push_back(upgrade);
}