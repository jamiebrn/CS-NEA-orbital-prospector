#include "Manager/EnemyShipManager.hpp"

std::vector<EnemyShip> EnemyShipManager::enemyShips;

void EnemyShipManager::addShip(sf::Vector2f position)
{
    EnemyShip ship(position);

    enemyShips.push_back(ship);
}

void EnemyShipManager::updateShips(float deltaTime)
{

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