#include "Manager/EnemyShipManager.hpp"

std::vector<EnemyShip> EnemyShipManager::enemyShips;
float EnemyShipManager::lastSpawn = 0;

void EnemyShipManager::addShip(EnemyShip ship)
{
    enemyShips.push_back(ship);
}

void EnemyShipManager::updateShips(sf::Vector2f playerPos, float deltaTime)
{

    for (auto iter = enemyShips.begin(); iter != enemyShips.end();)
    {

        iter->update(playerPos, enemyShips, deltaTime);

        if (!iter->isAlive())
        {
            iter = enemyShips.erase(iter);
            continue;
        }

        iter++;
    }

    lastSpawn += deltaTime;
    if (lastSpawn >= SPAWN_COOLDOWN)
    {
        lastSpawn = 0;

        float xPos = rand() % static_cast<int>(WORLD_WIDTH);
        float yPos = rand() % static_cast<int>(WORLD_HEIGHT);
        
        addShip(EnemyShip(sf::Vector2f(xPos, yPos)));
    }

}

void EnemyShipManager::drawShips(sf::RenderWindow& window)
{

    for (EnemyShip& ship : enemyShips)
    {
        ship.draw(window);
    }

}

void EnemyShipManager::reset()
{
    enemyShips.clear();
}

std::vector<EnemyShip>& EnemyShipManager::getShips()
{
    return enemyShips;
}