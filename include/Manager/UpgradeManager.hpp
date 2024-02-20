#ifndef UPGRADE_MANAGER_HPP
#define UPGRADE_MANAGER_HPP

#include <vector>
#include <unordered_map>
#include <json.hpp>

#include "Manager/TextureManager.hpp"

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

class UpgradeManager
{

private:
    UpgradeManager() = delete;

public:
    static bool hasUpgrade(UpgradeType upgrade);

    static void unlockUpgrade(UpgradeType upgrade);

    static inline void reset() {upgrades.clear();}

    static inline const std::vector<UpgradeType>& getUpgrades() {return upgrades;}

private:
    static std::vector<UpgradeType> upgrades;

};

inline const std::unordered_map<UpgradeType, TextureType> upgradeTextureMap =
{
    {UpgradeType::PrototypeEngine, TextureType::PrototypeEngine}
};

#endif