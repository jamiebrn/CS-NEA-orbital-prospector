#include "Manager/BulletManager.hpp"

std::vector<Bullet> BulletManager::bullets;
std::vector<Bullet> BulletManager::enemyBullets;

void BulletManager::createBullet(sf::Vector2f position, sf::Angle rotation)
{
    Bullet bullet(position, rotation);

    bullets.push_back(bullet);
}

void BulletManager::updateBullets(float deltaTime)
{
    for (Bullet& bullet : bullets)
    {
        bullet.update(deltaTime);
    }

    for (auto bulletIter = bullets.begin(); bulletIter != bullets.end();)
    {
        if (!bulletIter->isAlive())
        {
            bulletIter = bullets.erase(bulletIter);
        }
        else
        {
            bulletIter++;
        }
    }
}

void BulletManager::drawBullets(sf::RenderWindow& window)
{
    for (Bullet& bullet : bullets)
    {
        bullet.draw(window);
    }
}

void BulletManager::createEnemyBullet(sf::Vector2f position, sf::Angle rotation)
{
    Bullet bullet(position, rotation);

    enemyBullets.push_back(bullet);
}

void BulletManager::updateEnemyBullets(float deltaTime)
{
    for (Bullet& bullet : enemyBullets)
    {
        bullet.update(deltaTime);
    }

    for (auto bulletIter = enemyBullets.begin(); bulletIter != enemyBullets.end();)
    {
        if (!bulletIter->isAlive())
        {
            bulletIter = enemyBullets.erase(bulletIter);
        }
        else
        {
            bulletIter++;
        }
    }
}

void BulletManager::drawEnemyBullets(sf::RenderWindow& window)
{
    for (Bullet& bullet : enemyBullets)
    {
        bullet.draw(window);
    }
}

void BulletManager::reset()
{
    bullets.clear();
}

int BulletManager::getBulletCount()
{
    return bullets.size() + enemyBullets.size();
}

std::vector<Bullet>& BulletManager::getBullets()
{
    return bullets;
}

std::vector<Bullet>& BulletManager::getEnemyBullets()
{
    return enemyBullets;
}