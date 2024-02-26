// EnemyShipManager.hpp

#ifndef ENEMY_SHIP_MANAGER_HPP
#define ENEMY_SHIP_MANAGER_HPP

// Include libraries
#include <vector>
#include <SFML/Graphics.hpp>

// Include headers
#include "Objects/EnemyShip.hpp"
#include "Objects/PlayerShip.hpp"
#include "Constants.hpp"

// Declare enemy ship manager class
class EnemyShipManager
{

// Delete constructor, as is static class
private:
    EnemyShipManager() = delete;

// Public class functions
public:
    // Add enemy ship to manager
    static void addShip(EnemyShip ship);

    // Update all enemy ships
    static void updateShips(const PlayerShip& playerShip, float deltaTime);

    // Draw all enemy ships
    static void drawShips(sf::RenderWindow& window);

    // Delete all enemy ships
    static void reset();

    // Get reference to enemy ship vector
    static std::vector<EnemyShip>& getShips();

// Private member variables
private:
    // Vector containing all enemy ships
    static std::vector<EnemyShip> enemyShips;

    // Constant declaring how many enemy ships can exist
    static constexpr int MAX_SHIPS = 200;

    // Constant declaring how often enemy ships can spawn
    static constexpr float SPAWN_COOLDOWN = 20;

    // Variable keeping track of when an enemy ship was last spawned
    static float lastSpawn;

};

#endif