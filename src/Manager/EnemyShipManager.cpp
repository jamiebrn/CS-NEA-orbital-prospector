// EnemyShipManager.cpp

#include "Manager/EnemyShipManager.hpp"

// Initialise member variables, as is static class
std::vector<EnemyShip> EnemyShipManager::enemyShips;
float EnemyShipManager::lastSpawn = 0;

// Add enemy ship to vector
void EnemyShipManager::addShip(EnemyShip ship)
{
    // Add ship to vector
    enemyShips.push_back(ship);
}

// Update all enemy ships
void EnemyShipManager::updateShips(const PlayerShip& playerShip, float deltaTime)
{

    // Iterate over all enemy ships using an iterator, updating each and deleting them if required
    for (auto iter = enemyShips.begin(); iter != enemyShips.end();)
    {

        // Update enemy ship, taking parameters to interact with the game world
        iter->update(playerShip, enemyShips, deltaTime);

        // If the enemy ship can be removed, remove it
        if (iter->canRemove())
        {
            // Remove enemy ship from vector
            iter = enemyShips.erase(iter);
            continue;
        }

        // Increment iterator if enemy ship is not removed
        iter++;
    }

    // Add to last enemy ship spawn time
    lastSpawn += deltaTime;

    // If time since last spawn has reached spawn cooldown time,
    // and enemy ship count is below maximum, spawn new enemy ship
    if (lastSpawn >= SPAWN_COOLDOWN && enemyShips.size() < MAX_SHIPS)
    {
        // Reset time since last enemy ship spawn
        lastSpawn = 0;

        // Randomise position to anywhere in game world
        float xPos = rand() % static_cast<int>(WORLD_WIDTH);
        float yPos = rand() % static_cast<int>(WORLD_HEIGHT);
        
        // Add enemy ship to manager with generated position
        addShip(EnemyShip(sf::Vector2f(xPos, yPos)));
    }

}

// Draw all enemy ships
void EnemyShipManager::drawShips(sf::RenderWindow& window)
{
    // Iterate over all enemy ships and draw them
    for (EnemyShip& ship : enemyShips)
    {
        // Draw ship
        ship.draw(window);
    }

}

// Delete all enemy ships
void EnemyShipManager::reset()
{
    // Delete ships
    enemyShips.clear();
}

// Get a reference to enemy ship vector
std::vector<EnemyShip>& EnemyShipManager::getShips()
{
    // Return reference
    return enemyShips;
}