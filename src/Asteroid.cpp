#include "Asteroid.hpp"

Asteroid::Asteroid(sf::Vector2f position)
{
    this->position = position;
}

void Asteroid::update(float deltaTime)
{

}

void Asteroid::draw(sf::RenderWindow& window)
{

    sf::Vector2f drawOffset = Camera::getDrawOffset();

    TextureDrawData drawData = {
        TextureType::AsteroidCrack,
        position + drawOffset,
        sf::degrees(0),
        6
    };

    sf::IntRect subRect(sf::Vector2i(0, 0), sf::Vector2i(96, 96));

    TextureManager::drawSubTexture(window, drawData, subRect);

}
