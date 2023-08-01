#include "PlayerShip.hpp"

// Initialise player ship object
PlayerShip::PlayerShip()
{

    position = sf::Vector2f(WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2);
    velocity = sf::Vector2f(0, 0);
    direction = 0;

}

// Update player ship object position and rotation based on inputs
void PlayerShip::update(float deltaTime, sf::Vector2i mouse_position)
{

    sf::Angle destination_direction = sf::radians(std::atan2(mouse_position.y - position.y, mouse_position.x - position.x) + PI / 2);
    sf::Angle current_direction = Helper::lerpAngle(sf::radians(direction), destination_direction, ROTATION_LERP_WEIGHT * deltaTime);
    direction = current_direction.asRadians();

    if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
    {
        sf::Vector2f directionVector = sf::Vector2f(0, -1);
        directionVector = directionVector.rotatedBy(sf::radians(direction));

        velocity.x = Helper::lerp(velocity.x, directionVector.x * MAX_VELOCITY, ACCELERATION * deltaTime);
        velocity.y = Helper::lerp(velocity.y, directionVector.y * MAX_VELOCITY, ACCELERATION * deltaTime);
    }
    else
    {
        velocity.x = Helper::lerp(velocity.x, 0, DECELERATION * deltaTime);
        velocity.y = Helper::lerp(velocity.y, 0, DECELERATION * deltaTime);
    }

    position += velocity * deltaTime;

}

// Draw player ship object at position and rotation through texture manager
void PlayerShip::draw(sf::RenderWindow& window)
{

    TextureManager::drawTexture(window, TextureType::PlayerShip, position, sf::radians(direction), 4);

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