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

}

void EnemyShipManager::drawShips(sf::RenderWindow& window)
{

    for (EnemyShip& ship : enemyShips)
    {
        ship.draw(window);
    }

}

const std::vector<EnemyShip>& EnemyShipManager::getShips()
{
    return enemyShips;
}