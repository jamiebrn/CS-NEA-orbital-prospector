#include "Manager/EnemyShipManager.hpp"

std::vector<EnemyShip> EnemyShipManager::enemyShips;

void EnemyShipManager::addShip(sf::Vector2f position)
{
    EnemyShip ship(position);

    enemyShips.push_back(ship);
}

void EnemyShipManager::updateShips(sf::Vector2f playerPos, float deltaTime)
{

    for (auto iter = enemyShips.begin(); iter != enemyShips.end();)
    {

        iter->update(playerPos, deltaTime);

        if (!iter->isAlive())
        {
            iter = enemyShips.erase(iter);
            continue;
        }

        iter++;
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