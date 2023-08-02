#include "BulletManager.hpp"

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
}

void BulletManager::drawBullets(sf::RenderWindow& window)
{
    for (Bullet& bullet : bullets)
    {
        bullet.draw(window);
    }
}