#include "PlayerShip.hpp"

// Initialise player ship object
PlayerShip::PlayerShip()
{

    position = sf::Vector2f(WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2);
    velocity = sf::Vector2f(0, 0);
    direction = 0;

    shootCooldown = 0;

    engineAnimationIndex = 0;
    engineAnimTick = 0;
    engineActive = false;

}

// Update player ship object position and rotation based on inputs
void PlayerShip::update(float deltaTime, sf::Vector2i mouse_position)
{

    sf::Vector2f drawOffset = Camera::getDrawOffset();

    float toMouseAngle = std::atan2(mouse_position.y - position.y - drawOffset.y, mouse_position.x - position.x - drawOffset.x);
    sf::Angle destination_direction = sf::radians(toMouseAngle + PI / 2);
    sf::Angle current_direction = Helper::lerpAngle(sf::radians(direction), destination_direction, ROTATION_LERP_WEIGHT * deltaTime);
    direction = current_direction.asRadians();

    if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
    {
        sf::Vector2f directionVector = sf::Vector2f(0, -1);
        directionVector = directionVector.rotatedBy(sf::radians(direction));

        velocity.x = Helper::lerp(velocity.x, directionVector.x * MAX_VELOCITY, ACCELERATION * deltaTime);
        velocity.y = Helper::lerp(velocity.y, directionVector.y * MAX_VELOCITY, ACCELERATION * deltaTime);

        engineActive = true;
    }
    else
    {
        velocity.x = Helper::lerp(velocity.x, 0, DECELERATION * deltaTime);
        velocity.y = Helper::lerp(velocity.y, 0, DECELERATION * deltaTime);

        engineActive = false;
    }

    position += velocity * deltaTime;

    if (engineActive)
    {
        engineAnimTick += deltaTime;
        if (engineAnimTick >= ENGINE_ANIM_TICK_MAX)
        {
            engineAnimTick = 0;
            engineAnimationIndex = (engineAnimationIndex + 1) % 10;
        }
    }

    shootCooldown += deltaTime;

    if (sf::Mouse::isButtonPressed(sf::Mouse::Right) && shootCooldown >= SHOOT_COOLDOWN)
    {
        shootCooldown = 0;
        shootBullets();
    }

}

void PlayerShip::shootBullets()
{

    for (sf::Vector2f spawnPos : bulletSpawnPos)
    {
        sf::Vector2f globalPosition = position;
        globalPosition += spawnPos.rotatedBy(sf::radians(direction)) * 4.0f;

        BulletManager::createBullet(globalPosition, sf::radians(direction));
    }


}

// Draw player ship object at position and rotation through texture manager
void PlayerShip::draw(sf::RenderWindow& window)
{

    sf::Vector2f drawOffset = Camera::getDrawOffset();

    if (engineActive)
    {
        TextureDrawData engineDrawData = {
            TextureType::PlayerShipEngine,
            position + drawOffset,
            sf::radians(direction),
            4
        };

        sf::IntRect engineSubRect = sf::IntRect(sf::Vector2i(64 * engineAnimationIndex, 0), sf::Vector2i(64, 64));

        TextureManager::drawSubTexture(window, engineDrawData, engineSubRect);
    }

    TextureDrawData shipDrawData = {
        TextureType::PlayerShip,
        position + drawOffset,
        sf::radians(direction),
        4
    };

    TextureManager::drawTexture(window, shipDrawData);

}

// Set player ship position
void PlayerShip::setPosition(sf::Vector2f new_position)
{
    position = new_position;
}

// Get player ship position
sf::Vector2f PlayerShip::getPosition()
{
    return position;
}