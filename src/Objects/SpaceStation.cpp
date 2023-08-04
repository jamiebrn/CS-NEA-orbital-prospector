#include "Objects/SpaceStation.hpp"


SpaceStation::SpaceStation()
{
    orbitAngle = 0;
}

SpaceStation::SpaceStation(sf::Vector2f position, sf::Angle rotation)
{
    this->position = position;
    this->rotation = rotation;

    orbitAngle = 0;
}

void SpaceStation::setPosition(sf::Vector2f position)
{
    this->position = position;
}

sf::Vector2f SpaceStation::getPosition()
{
    return position;
}

void SpaceStation::setRotation(sf::Angle rotation)
{
    this->rotation = rotation;
}

// Centre position must be normalised to space station depth
void SpaceStation::orbitBody(sf::Vector2f centre, float radius, float speed, float deltaTime)
{

    orbitAngle += speed * deltaTime;
    if (orbitAngle >= 360)
        orbitAngle = 0;

    sf::Vector2f rotatedLocalPos = sf::Vector2f(0, -1).rotatedBy(sf::degrees(orbitAngle));
    sf::Vector2f rotatedPos = (rotatedLocalPos * radius) + centre;

    position = rotatedPos;

}

void SpaceStation::draw(sf::RenderWindow& window)
{

    sf::Vector2f drawOffset = Camera::getDrawOffset();

    TextureDrawData drawData = {
        TextureType::SpaceStation,
        position + drawOffset / 1.1f,
        rotation,
        6
    };

    TextureManager::drawTexture(window, drawData);

}