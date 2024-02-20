#include "Manager/UpgradeManager.hpp"

std::vector<UpgradeType> UpgradeManager::upgrades;

bool UpgradeManager::hasUpgrade(UpgradeType upgrade)
{
    if (upgrade == UpgradeType::NONE)
        return true;

    for (UpgradeType type : upgrades)
    {
        if (type == upgrade) return true;
    }

    return false;
}

void UpgradeManager::unlockUpgrade(UpgradeType upgrade)
{
    upgrades.push_back(upgrade);
}