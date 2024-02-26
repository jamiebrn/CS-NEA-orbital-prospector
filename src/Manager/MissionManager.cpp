// MissionManager.cpp

#include "Manager/MissionManager.hpp"

// Initialise member variables, as is static class
std::array<Mission, 3> MissionManager::missions;
int MissionManager::acceptedMission = -1;
int MissionManager::goalProgress = 0;

// Generate a new random mission
void MissionManager::generateMission(int id)
{
    // Create new mission object
    Mission mission;

    // Set mission type to random selection
    mission.type = MissionType(rand() % static_cast<int>(MissionType::END_ENUM));

    // Set mission data values depending on mission type
    switch (mission.type)
    {
        // Collection mission type
        case MissionType::Collect:
        {
            // Set goal amount
            mission.goalAmount = (rand() % 21) + 5;

            // Set base reward amount
            mission.reward = mission.goalAmount * 4;

            // Modify reward amount randomly based on set range
            mission.reward += static_cast<float>(mission.reward) * (((rand() % 21) - 10.0f) / 100.0f);

            // Set mission title
            mission.title = "Collect " + std::to_string(mission.goalAmount) + " items";
            break;
        }
        
        // Kill mission type
        case MissionType::Kill:
        {
            // Set goal amount
            mission.goalAmount = (rand() % 11) + 1;

            // Set base reward amount
            mission.reward = mission.goalAmount * 8;

            // Modify reward amount randomly based on set range
            mission.reward += static_cast<float>(mission.reward) * (((rand() % 31) - 15.0f) / 100.0f);

            // Set mission title
            mission.title = "Kill " + std::to_string(mission.goalAmount) + " enemies";
            break;
        }
    }

    // Set mission description based on mission title and reward
    mission.description = (mission.title + " for a reward of " +
        std::to_string(mission.reward) + " silver coins");
    
    // Set mission at ID in array to generated mission data
    missions[id] = mission;

}

// Randomise all missions
void MissionManager::rerollAllMissions()
{
    // Generate new mission for all missions
    for (int i = 0; i < missions.size(); i++)
    {
        // Generate new mission
        generateMission(i);
    }

}

// Get data of a specific mission
const Mission& MissionManager::getMissionData(int id)
{
    // Return mission data at ID
    return missions[id];
}

// Override specific mission
void MissionManager::setMissionData(int id, const Mission& mission)
{
    // Set mission data at ID to mission data
    missions[id] = mission;
}

// Accept specific mission
void MissionManager::acceptMission(int id)
{
    // If mission already in progress, don't attempt to accept new mission
    if (hasAcceptedMission())
        return;

    // If no mission in progress, set current mission to ID
    acceptedMission = id;

    // Reset mission goal progress (as new mission has started)
    goalProgress = 0;

}

// Returns whether a mission is in progress (has been accepted)
bool MissionManager::hasAcceptedMission()
{
    // If accepted mission is not -1, a mission is in progress
    return (acceptedMission != -1);
}

// Returns whether the current mission goal has been met
bool MissionManager::missionCompleted()
{
    // If mission not in progress, return false by default
    if (!hasAcceptedMission())
        return false;
    
    // Return whether mission progress is at least mission goal amount
    return (goalProgress >= missions.at(acceptedMission).goalAmount);
}

// Completes a mission (gives rewards, generates new mission)
void MissionManager::completeMission()
{
    // If mission not in progress, return by default
    if (!hasAcceptedMission())
        return;
    
    // If current mission is completed, give rewards and generate new mission
    if (missionCompleted())
    {
        // Add silver coins reward
        InventoryManager::addSilverCoins(missions.at(acceptedMission).reward);

        // Generate new mission at ID of current mission
        generateMission(acceptedMission);

        // Set accepted mission to -1 (meaning no mission)
        acceptedMission = -1;
    }
}

// Add to mission goal, with specific mission type and amount to add
void MissionManager::addToGoal(MissionType type, int amount)
{
    // If mission not in progress, return by default
    if (!hasAcceptedMission())
        return;
    
    // If goal type attempting to add to is equal to type of current mission, add amount to goal progress
    if (missions.at(acceptedMission).type == type)
    {
        // Add to goal progress
        goalProgress += amount;
    }
}

// Get the ID of the mission which is in progress
int MissionManager::getAcceptedMissionId()
{
    // Return current mission ID
    return acceptedMission;
}

// Get progress on current mission
int MissionManager::getGoalProgress()
{
    // Return current mission goal progress
    return goalProgress;
}