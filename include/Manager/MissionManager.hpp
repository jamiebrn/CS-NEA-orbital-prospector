// MissionManager.hpp

#ifndef MISSION_MANAGER_HPP
#define MISSION_MANAGER_HPP

// Include libraries
#include <string>
#include <array>
#include <json.hpp>

// Include headers
#include "Manager/InventoryManager.hpp"

// Enum containing all different type of missions
enum class MissionType
{
    Collect,
    Kill,

    END_ENUM // Exists so "length" of enum can be found
};

// Struct containing all mission data
struct Mission
{
    // Title and description of mission
    std::string title, description;

    // Type of mission
    MissionType type;

    // Amount of requirement to complete mission, depending on type of mission (e.g. collect items or kill enemies)
    int goalAmount;

    // Reward in silver coins for completing mission
    int reward;

    // Macro used for (de)serialisation when saving game data
    NLOHMANN_DEFINE_TYPE_INTRUSIVE(Mission,
        title, description, type, goalAmount, reward
    )
};

// Declare mission manager class
class MissionManager
{

// Delete constructor, as is static class
private:
    MissionManager() = delete;

// Public class funcions
public:
    // Generate a new random mission
    static void generateMission(int id);

    // Randomise all missions
    static void rerollAllMissions();

    // Get data of a specific mission
    static const Mission& getMissionData(int id);

    // Override specific mission
    static void setMissionData(int id, const Mission& mission);

    // Accept specific mission
    static void acceptMission(int id);

    // Returns whether a mission is in progress (has been accepted)
    static bool hasAcceptedMission();

    // Returns whether the current mission goal has been met
    static bool missionCompleted();

    // Completes a mission (gives rewards, generates new mission)
    static void completeMission();

    // Add to mission goal, with specific mission type and amount to add
    static void addToGoal(MissionType type, int amount);

    // Get the ID of the mission which is in progress
    static int getAcceptedMissionId();

    // Get progress on current mission
    static int getGoalProgress();

// Private member variables
private:
    // Array of size 3, storing all missions
    static std::array<Mission, 3> missions;

    // Variable storing ID of current mission
    static int acceptedMission;

    // Variable storing progress on current mission
    static int goalProgress;

};

#endif