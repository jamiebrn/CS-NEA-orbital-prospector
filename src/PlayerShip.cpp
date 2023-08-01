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

    direction = std::atan2(mouse_position.y - position.y, mouse_position.x - position.x) + PI / 2;

    if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
    {
        sf::Vector2f toMouseVector = sf::Vector2f(mouse_position.x - position.x, mouse_position.y - position.y);
        if (toMouseVector.lengthSq() > 1)
            toMouseVector = toMouseVector.normalized();

        position += toMouseVector * SPEED * deltaTime;
    }

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