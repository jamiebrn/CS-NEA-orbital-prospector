#include "Objects/EnemyShip.hpp"

EnemyShip::EnemyShip(sf::Vector2f position)
{

    this->position = position;

    velocity = sf::Vector2f(0, 0);
    rotation = sf::degrees(0);

}

void EnemyShip::update(sf::Vector2f playerPos, float deltaTime)
{

    sf::Angle destRot = (position - playerPos).angle() - sf::degrees(90);
    rotation = Helper::lerpAngle(rotation, destRot, ROTATION_LERP_WEIGHT * deltaTime);

    float distanceSq = (position - playerPos).lengthSq();
    if (distanceSq >= PLAYER_SHOOT_RADIUS * PLAYER_SHOOT_RADIUS)
    {
        sf::Vector2f directionVector = sf::Vector2f(0, -1).rotatedBy(rotation);

        velocity.x = Helper::lerp(velocity.x, directionVector.x * SPEED, ACCELERATION * deltaTime);
        velocity.y = Helper::lerp(velocity.y, directionVector.y * SPEED, ACCELERATION * deltaTime);
    }
    else
    {
        velocity.x = Helper::lerp(velocity.x, 0, DECELERATION * deltaTime);
        velocity.y = Helper::lerp(velocity.y, 0, DECELERATION * deltaTime);
    }

    position += velocity * deltaTime;

}

void EnemyShip::draw(sf::RenderWindow& window)
{

    sf::Vector2f drawOffset = Camera::getDrawOffset();

    TextureDrawData drawData = {
        TextureType::EnemyShip,
        position + drawOffset,
        rotation,
        5
    };

    TextureManager::drawTexture(window, drawData);

}

sf::Vector2f EnemyShip::getPosition() const
{
    return position;
}