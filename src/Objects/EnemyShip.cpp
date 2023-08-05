#include "Objects/EnemyShip.hpp"

EnemyShip::EnemyShip(sf::Vector2f position)
{

    this->position = position;

    velocity = sf::Vector2f(0, 0);
    rotation = sf::degrees(0);

}

void EnemyShip::update(sf::Vector2f playerPos, float deltaTime)
{



}

void EnemyShip::draw(sf::RenderWindow& window)
{

    sf::Vector2f drawOffset = Camera::getDrawOffset();

    TextureDrawData drawData = {
        TextureType::EnemyShip,
        position + drawOffset,
        rotation,
        4
    };

    TextureManager::drawTexture(window, drawData);

}

sf::Vector2f EnemyShip::getPosition() const
{
    return position;
}