#ifndef ENEMY_SHIP_MANAGER_HPP
#define ENEMY_SHIP_MANAGER_HPP

#include <vector>

#include <SFML/Graphics.hpp>

#include "Objects/EnemyShip.hpp"

class EnemyShipManager
{

private:
    EnemyShipManager() = delete;

public:
    static void addShip(sf::Vector2f position);

    static void updateShips(sf::Vector2f playerPos, float deltaTime);

    static void drawShips(sf::RenderWindow& window);

    static const std::vector<EnemyShip>& getShips();

private:
    static std::vector<EnemyShip> enemyShips;

};

#endif