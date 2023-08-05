#ifndef HEALTH_BAR_HPP
#define HEALTH_BAR_HPP

#include <SFML/Graphics.hpp>

#include "DrawableObject.hpp"

class HealthBar : public DrawableObject
{

public:
    HealthBar(sf::Vector2f position, sf::Vector2f size, float maxValue);

    void updateValue(float value);

    void setDrawPosition(sf::Vector2f position);

    void draw(sf::RenderWindow& window) override;

private:
    sf::Vector2f position, size;

    float maxValue, value;

};

#endif