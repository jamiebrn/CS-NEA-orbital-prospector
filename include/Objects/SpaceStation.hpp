// SpaceStation.hpp

#ifndef SPACE_STATION_HPP
#define SPACE_STATION_HPP

// Include libraries
#include <SFML/Graphics.hpp>

// Include headers
#include "Constants.hpp"
#include "Camera.hpp"
#include "Objects/DrawableObject.hpp"
#include "Manager/TextureManager.hpp"

// Declare space station class
class SpaceStation : public DrawableObject
{

// Public class functions
public:
    // Constructor taking in no parameters
    SpaceStation();
    // Constructor taking in position and rotation
    SpaceStation(sf::Vector2f position, sf::Angle rotation);

    // Set space station position
    void setPosition(sf::Vector2f position);
    // Get space station position
    sf::Vector2f getPosition();

    // Set space station rotation
    void setRotation(sf::Angle rotation);

    // Override space station position to orbit around a position
    // Centre position must be normalised to space station depth
    void orbitBody(sf::Vector2f centre, float radius, float speed, float deltaTime);

    // Override angle of orbit
    void setOrbitAngle(float angle);
    // Get angle of orbit
    float getOrbitAngle();

    // Draw space station
    void draw(sf::RenderWindow& window) override;

// Private member variables
private:
    // Variables storing position and rotation
    sf::Vector2f position;
    sf::Angle rotation;

    // Variables storing angle of orbit
    float orbitAngle;

};

#endif