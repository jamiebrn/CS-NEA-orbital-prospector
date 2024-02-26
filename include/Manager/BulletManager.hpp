// BulletManager.hpp

#ifndef BULLET_MANAGER_HPP
#define BULLET_MANAGER_HPP

// Include libraries
#include <vector>
#include <SFML/Graphics.hpp>

// Include headers
#include "Objects/Bullet.hpp"

// Declare bullet manager class
class BulletManager
{

// Delete constructor as is a static class
private:
    BulletManager() = delete;

// Public class functions
public:
    // Create a player ship bullet with position and rotation
    static void createBullet(sf::Vector2f position, sf::Angle rotation);

    // Update all player ship bullets
    static void updateBullets(float deltaTime);

    // Draw all player ship bullets
    static void drawBullets(sf::RenderWindow& window);

    // Create a bullet from an enemy ship
    static void createEnemyBullet(sf::Vector2f position, sf::Angle rotation);

    // Update all enemy ship bullets
    static void updateEnemyBullets(float deltaTime);

    // Draw all enemy ship bullets
    static void drawEnemyBullets(sf::RenderWindow& window);

    // Delete all player ship and enemy ship bullets
    static void reset();

    // Get total amount of bullets
    static int getBulletCount();

    // Get reference to player ship bullet vector
    static std::vector<Bullet>& getBullets();

    // Get reference to enemy ship bullet vector
    static std::vector<Bullet>& getEnemyBullets();

// Private member variables
private:
    // Player ship bullet vector
    static std::vector<Bullet> bullets;

    // Enemy ship bullet vector
    static std::vector<Bullet> enemyBullets;

};

#endif