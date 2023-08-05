#include "Manager/EnemyShipManager.hpp"

std::vector<EnemyShip> EnemyShipManager::enemyShips;

void EnemyShipManager::addShip(sf::Vector2f position)
{
    EnemyShip ship(position);

    enemyShips.push_back(ship);
}

void EnemyShipManager::updateShips(sf::Vector2f playerPos, float deltaTime)
{

    for (EnemyShip& ship : enemyShips)
    {
        ship.update(playerPos, deltaTime);
    }

    for (int i = 0; i < enemyShips.size();)
    {

        if (!enemyShips[i].isAlive())
        {
            enemyShips.erase(enemyShips.begin() + i);
            continue;
        }

        i++;
    }

}

void EnemyShipManager::drawShips(sf::RenderWindow& window)
{

    for (EnemyShip& ship : enemyShips)
    {
        ship.draw(window);
    }

}

std::vector<EnemyShip>& EnemyShipManager::getShips()
{
    return enemyShips;
}