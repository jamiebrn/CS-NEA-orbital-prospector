#ifndef MISSION_MANAGER_HPP
#define MISSION_MANAGER_HPP

#include <string>
#include <array>
#include <json.hpp>

#include "Manager/InventoryManager.hpp"

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

    static void setMissionData(int id, const Mission& mission);

    static void acceptMission(int id);

    static bool hasAcceptedMission();

    static bool missionCompleted();

    static void completeMission();

    static void addToGoal(MissionType type, int amount);

    static int getAcceptedMissionId();

    static int getGoalProgress();

private:
    static std::array<Mission, 3> missions;

    static int acceptedMission;

    static int goalProgress;

};

#endif