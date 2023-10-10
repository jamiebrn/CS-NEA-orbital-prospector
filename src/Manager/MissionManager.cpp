#include "Manager/MissionManager.hpp"

std::array<Mission, 3> MissionManager::missions;
int MissionManager::acceptedMission = -1;
int MissionManager::goalProgress = 0;

void MissionManager::generateMission(int id)
{

    Mission mission;
    mission.type = MissionType(rand() % static_cast<int>(MissionType::END_ENUM));

    switch (mission.type)
    {
        case MissionType::Collect:
        {
            mission.goalAmount = (rand() % 21) + 5;
            mission.reward = mission.goalAmount * 4;
            mission.reward += static_cast<float>(mission.reward) * (((rand() % 21) - 10.0f) / 100.0f);
            mission.title = "Collect " + std::to_string(mission.goalAmount) + " items";
            break;
        }
        
        case MissionType::Kill:
        {
            mission.goalAmount = (rand() % 11) + 1;
            mission.reward = mission.goalAmount * 8;
            mission.reward += static_cast<float>(mission.reward) * (((rand() % 31) - 15.0f) / 100.0f);
            mission.title = "Kill " + std::to_string(mission.goalAmount) + " enemies";
            break;
        }
    }

    mission.description = (mission.title + " for a reward of " +
        std::to_string(mission.reward) + " silver coins");
    
    missions[id] = mission;

}

void MissionManager::rerollAllMissions()
{

    for (int i = 0; i < missions.size(); i++)
    {
        generateMission(i);
    }

}

const Mission& MissionManager::getMissionData(int id)
{
    return missions[id];
}

void MissionManager::setMissionData(int id, const Mission& mission)
{
    missions[id] = mission;
}

void MissionManager::acceptMission(int id)
{

    if (hasAcceptedMission())
        return;

    acceptedMission = id;
    goalProgress = 0;

}

bool MissionManager::hasAcceptedMission()
{
    return (acceptedMission != -1);
}

bool MissionManager::missionCompleted()
{
    if (!hasAcceptedMission())
        return false;

    return (goalProgress >= missions.at(acceptedMission).goalAmount);
}

void MissionManager::completeMission()
{
    if (!hasAcceptedMission())
        return;

    if (missionCompleted())
    {
        InventoryManager::addSilverCoins(missions.at(acceptedMission).reward);
        generateMission(acceptedMission);
        acceptedMission = -1;
    }
}

void MissionManager::addToGoal(MissionType type, int amount)
{
    if (!hasAcceptedMission())
        return;

    if (missions.at(acceptedMission).type == type)
    {
        goalProgress += amount;
    }
}

int MissionManager::getAcceptedMissionId()
{
    return acceptedMission;
}

int MissionManager::getGoalProgress()
{
    return goalProgress;
}