#ifndef ENEMY_SHIP_MANAGER_HPP
#define ENEMY_SHIP_MANAGER_HPP

#include <vector>

#include <SFML/Graphics.hpp>

#include "Objects/EnemyShip.hpp"
#include "Constants.hpp"

class EnemyShipManager
{

private:
    EnemyShipManager() = delete;

public:
    static void addShip(EnemyShip ship);

    static void updateShips(sf::Vector2f playerPos, float deltaTime);

    static void drawShips(sf::RenderWindow& window);

    static void reset();

    static std::vector<EnemyShip>& getShips();

private:
    static std::vector<EnemyShip> enemyShips;

    static constexpr float SPAWN_COOLDOWN = 10;

    static float lastSpawn;

};

#endif