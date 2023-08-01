#include "PlayerShip.hpp"

PlayerShip::PlayerShip()
{

    position = sf::Vector2f(WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2);
    direction = 0;

    rect.setSize(sf::Vector2f(50, 70));
    rect.setOrigin(sf::Vector2f(25, 35));
    rect.setFillColor(sf::Color(220, 220, 220));

    rect.setPosition(position);
    rect.setRotation(sf::radians(direction));

}

void PlayerShip::update(float deltaTime, sf::Vector2i mouse_position)
{

    direction = std::atan2(mouse_position.y - position.y, mouse_position.x - position.x) + PI / 2;

    if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
    {
        sf::Vector2f toMouseVector = sf::Vector2f(mouse_position.x - position.x, mouse_position.y - position.y);
        if (toMouseVector.lengthSq() != 0)
            toMouseVector = toMouseVector.normalized();

        position += toMouseVector * SPEED * deltaTime;
    }

    rect.setPosition(position);
    rect.setRotation(sf::radians(direction));

}

void PlayerShip::draw(sf::RenderWindow& window)
{

    TextureManager::drawTexture(window, TextureType::PlayerShip, position, sf::radians(direction), 4);

}

void PlayerShip::setPosition(sf::Vector2f new_position)
{
    position = new_position;
}

sf::Vector2f PlayerShip::getPosition()
{
    return position;
}