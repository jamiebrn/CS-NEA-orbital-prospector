#include "Camera.hpp"

sf::Vector2f Camera::offset = sf::Vector2f(0, 0);

void Camera::update(sf::Vector2f playerPosition, float deltaTime)
{
    sf::Vector2f destinationOffset;
    destinationOffset.x = playerPosition.x - WINDOW_WIDTH / 2;
    destinationOffset.y = playerPosition.y - WINDOW_HEIGHT / 2;

    offset.x = Helper::lerp(offset.x, destinationOffset.x, MOVE_LERP_WEIGHT * deltaTime);
    offset.y = Helper::lerp(offset.y, destinationOffset.y, MOVE_LERP_WEIGHT * deltaTime);

    offset.x = std::clamp(offset.x, 0.0f, WORLD_WIDTH);
    offset.y = std::clamp(offset.y, 0.0f, WORLD_HEIGHT);
}

sf::Vector2f Camera::getDrawOffset()
{
    sf::Vector2f drawOffset = -offset;
    
    return drawOffset;
}

void Camera::setOffset(sf::Vector2f newOffset)
{
    offset = newOffset;
}