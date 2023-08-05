#include "Objects/Bullet.hpp"

Bullet::Bullet(sf::Vector2f initPosition, sf::Angle initRotation)
{
    position = initPosition;
    rotation = initRotation;

    velocity = sf::Vector2f(0, -1).rotatedBy(rotation) * SPEED;

    animTick = 0;
    animIndex = rand() % MAX_ANIM_FRAMES;

    timeAlive = 0;
}

void Bullet::update(float deltaTime)
{
    position += velocity * deltaTime;

    animTick += deltaTime;
    if (animTick >= MAX_ANIM_TICK)
    {
        animTick = 0;
        animIndex = (animIndex + 1) % MAX_ANIM_FRAMES;
    }

    timeAlive += deltaTime;

    checkCollisions();

}

void Bullet::checkCollisions()
{

    for (Asteroid& asteroid : AsteroidManager::getAsteroids())
    {
        if (asteroid.isColliding(position))
        {
            timeAlive = LIFETIME;
        }
    }

    for (EnemyShip& ship : EnemyShipManager::getShips())
    {
        if (ship.isBulletColliding(position))
        {
            timeAlive = LIFETIME;
        }
    }

}

bool Bullet::isAlive()
{
    return (timeAlive < LIFETIME);
}

void Bullet::draw(sf::RenderWindow& window)
{

    sf::Vector2f drawOffset = Camera::getDrawOffset();

    TextureDrawData bulletDrawData = {
        TextureType::Bullet,
        position + drawOffset,
        rotation,
        4
    };

    sf::IntRect bulletSubRect = sf::IntRect(sf::Vector2i(animIndex * 4, 0), sf::Vector2i(4, 16));

    TextureManager::drawSubTexture(window, bulletDrawData, bulletSubRect);

}