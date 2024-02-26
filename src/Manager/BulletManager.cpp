// BulletManager.cpp

#include "Manager/BulletManager.hpp"

// Initialise member variables, as is static class
std::vector<Bullet> BulletManager::bullets;
std::vector<Bullet> BulletManager::enemyBullets;

// Create player ship bullet
void BulletManager::createBullet(sf::Vector2f position, sf::Angle rotation)
{
    // Create bullet with parameters
    Bullet bullet(position, rotation);

    // Add bullet to player ship bullet vector
    bullets.push_back(bullet);
}

// Update player ship bullets
void BulletManager::updateBullets(float deltaTime)
{
    // Iterate over all player ship bullets and update them
    for (Bullet& bullet : bullets)
    {
        // Update bullet
        bullet.update(deltaTime);
    }

    // Iterate over all player ship bullets using an iterator, in order to remove any destroyed bullets
    for (auto bulletIter = bullets.begin(); bulletIter != bullets.end();)
    {
        // If bullet is no longer alive, delete it
        if (!bulletIter->isAlive())
        {
            // Delete bullet from vector
            bulletIter = bullets.erase(bulletIter);
        }
        else
        {
            // Increment iterator if bullet was not removed
            bulletIter++;
        }
    }
}

// Draw player ship bullets
void BulletManager::drawBullets(sf::RenderWindow& window)
{
    // Iterate over all player ship bullets and draw them
    for (Bullet& bullet : bullets)
    {
        // Draw bullet
        bullet.draw(window);
    }
}

// Create enemy ship bullet
void BulletManager::createEnemyBullet(sf::Vector2f position, sf::Angle rotation)
{
    // Create bullet with parameters
    Bullet bullet(position, rotation);

    // Add bullet to enemy ship bullet vector
    enemyBullets.push_back(bullet);
}

// Update enemy ship bullets
void BulletManager::updateEnemyBullets(float deltaTime)
{
    // Iterate over all enemy ship bullets and update them
    for (Bullet& bullet : enemyBullets)
    {
        // Update bullet
        bullet.update(deltaTime);
    }

    // Iterate over all enemy ship bullets using an iterator, and remove bullets if they are destroyed
    for (auto bulletIter = enemyBullets.begin(); bulletIter != enemyBullets.end();)
    {
        // If bullet is not alive, delete it
        if (!bulletIter->isAlive())
        {
            // Delete bullet
            bulletIter = enemyBullets.erase(bulletIter);
        }
        else
        {
            // If bullet is still alive, increment iterator
            bulletIter++;
        }
    }
}

// Draw all enemy ship bullets
void BulletManager::drawEnemyBullets(sf::RenderWindow& window)
{
    // Iterate over all enemy ship bullets and draw them
    for (Bullet& bullet : enemyBullets)
    {
        // Draw bullet
        bullet.draw(window);
    }
}

// Delete all bullets
void BulletManager::reset()
{
    // Delete player ship bullets
    bullets.clear();

    // Delet enemy ship bullets
    enemyBullets.clear();
}

// Get total bullet count
int BulletManager::getBulletCount()
{
    // Return amount of player ship bullets + enemy ship bullets
    return bullets.size() + enemyBullets.size();
}

// Get reference to player ship bullet vector
std::vector<Bullet>& BulletManager::getBullets()
{
    // Return reference
    return bullets;
}

// Get reference to enemy ship bullet vector
std::vector<Bullet>& BulletManager::getEnemyBullets()
{
    // Return reference
    return enemyBullets;
}