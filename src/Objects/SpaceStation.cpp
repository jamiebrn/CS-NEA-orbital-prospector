// SpaceStation.cpp

#include "Objects/SpaceStation.hpp"

// Constructor taking in no parameters
SpaceStation::SpaceStation()
{
    // Initialise orbit angle
    orbitAngle = 0;
}

// Constructor taking in position and rotation
SpaceStation::SpaceStation(sf::Vector2f position, sf::Angle rotation)
{
    // Set position and rotation from parameters
    this->position = position;
    this->rotation = rotation;

    // Initialise orbit angle
    orbitAngle = 0;
}

// Set space station position
void SpaceStation::setPosition(sf::Vector2f position)
{
    this->position = position;
}

// Get space station position
sf::Vector2f SpaceStation::getPosition()
{
    return position;
}

// Set space station rotation
void SpaceStation::setRotation(sf::Angle rotation)
{
    this->rotation = rotation;
}

// Override space station position to orbit around a position
// Centre position must be normalised to space station depth
void SpaceStation::orbitBody(sf::Vector2f centre, float radius, float speed, float deltaTime)
{
    // Add to orbit angle with certain speed
    orbitAngle += speed * deltaTime;
    // Reset orbit angle to 0 if angle is 360 or over
    if (orbitAngle >= 360)
        orbitAngle = 0;
    
    // Calculate position of space station
    sf::Vector2f rotatedLocalPos = sf::Vector2f(0, -1).rotatedBy(sf::degrees(orbitAngle));
    sf::Vector2f rotatedPos = (rotatedLocalPos * radius) + centre;

    // Set position to calculate position
    position = rotatedPos;

}

// Override angle of orbit
void SpaceStation::setOrbitAngle(float angle)
{
    orbitAngle = angle;
}

// Get angle of orbit
float SpaceStation::getOrbitAngle()
{
    return orbitAngle;
}

// Draw space station
void SpaceStation::draw(sf::RenderWindow& window)
{
    // Get draw offset
    sf::Vector2f drawOffset = Camera::getDrawOffset();

    // Create draw data for space station
    TextureDrawData drawData = {
        TextureType::SpaceStation,
        position + drawOffset / SPACE_STATION_DEPTH_DIVIDE,
        rotation,
        6
    };

    // Draw space station sprite
    TextureManager::drawTexture(window, drawData);
}