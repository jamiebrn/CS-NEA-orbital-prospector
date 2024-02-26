#ifndef SPACE_STATION_HPP
#define SPACE_STATION_HPP

#include <SFML/Graphics.hpp>

#include "Constants.hpp"
#include "Camera.hpp"
#include "Objects/DrawableObject.hpp"
#include "Manager/TextureManager.hpp"

class SpaceStation : public DrawableObject
{

public:
    SpaceStation();
    SpaceStation(sf::Vector2f position, sf::Angle rotation);

    void setPosition(sf::Vector2f position);
    sf::Vector2f getPosition();

    void setRotation(sf::Angle rotation);

    void orbitBody(sf::Vector2f centre, float radius, float speed, float deltaTime);

    void setOrbitAngle(float angle);
    float getOrbitAngle();

    void draw(sf::RenderWindow& window) override;

private:
    sf::Vector2f position;
    sf::Angle rotation;

    float orbitAngle;

};

#endif