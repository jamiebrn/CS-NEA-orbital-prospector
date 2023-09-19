#ifndef HEALTH_BAR_HPP
#define HEALTH_BAR_HPP

#include <SFML/Graphics.hpp>

#include "DrawableObject.hpp"
#include "Helper.hpp"

class HealthBar : public DrawableObject
{

public:
    HealthBar(sf::Vector2f position, sf::Vector2f size, float maxValue);

    void update(float deltaTime);

    void updateValue(float value);

    void setMaxValue(float value);

    void reset();

    void setDrawPosition(sf::Vector2f position);

    void setFillColour(sf::Color colour);

    void draw(sf::RenderWindow& window) override;

    inline float getMaxValue() {return maxValue;}

    inline float getValue() {return value;}

    inline float getDestValue() {return destValue;}

private:
    static constexpr float LERP_WEIGHT = 5;

    sf::Vector2f position, size;

    sf::Color fillColour;

    float maxValue, value, destValue;

};

#endif