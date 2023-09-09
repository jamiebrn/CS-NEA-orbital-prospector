#include "Manager/BulletManager.hpp"

std::vector<Bullet> BulletManager::bullets;

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

void BulletManager::empty()
{
    bullets.clear();
}

int BulletManager::getBulletCount()
{
    return bullets.size();
}