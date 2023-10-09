#ifndef MISSION_MANAGER_HPP
#define MISSION_MANAGER_HPP

#include <string>
#include <array>
#include <json.hpp>

enum class MissionType
{
    Collect,
    Kill,

    END_ENUM
};

struct Mission
{
    std::string title, description;
    MissionType type;
    int goalAmount;
    int reward;

    NLOHMANN_DEFINE_TYPE_INTRUSIVE(Mission,
        title, description, type, goalAmount, reward
    )
};

class MissionManager
{

private:
    MissionManager() = delete;

public:
    static void generateMission(int id);

    static void rerollAllMissions();

    static const Mission& getMissionData(int id);

private:
    static std::array<Mission, 3> missions;

};

#endif