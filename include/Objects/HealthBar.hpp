// HealthBar.hpp

#ifndef HEALTH_BAR_HPP
#define HEALTH_BAR_HPP

// Include libraries
#include <SFML/Graphics.hpp>

// Include headers
#include "DrawableObject.hpp"
#include "Helper.hpp"

// Declare health bar class
class HealthBar : public DrawableObject
{

// Public class functions
public:
    // Constructor taking in position, size, and maximum value of health bar
    HealthBar(sf::Vector2f position, sf::Vector2f size, float maxValue);

    // Update the health bar
    void update(float deltaTime);

    // Update the current value of the health bar
    void updateValue(float value);

    // Set the max value of the health bar
    void setMaxValue(float value);

    // Reset the health bar current value to 0
    void reset();

    // Set health bar draw position on screen
    void setDrawPosition(sf::Vector2f position);

    // Set the fill colour of the health bar
    void setFillColour(sf::Color colour);

    // Draw the health bar
    void draw(sf::RenderWindow& window) override;

    // Set the width of the health bar
    inline void setWidth(float width) {size.x = width;}

    // Get the max health value
    inline float getMaxValue() {return maxValue;}

    // Get the current health value
    inline float getValue() {return value;}

    // Get the "actual" health value (the value shown on the bar is updated over time to give an animated effect, so may not be the exact health value)
    inline float getDestValue() {return destValue;}

// Private member variables
private:
    // Constant storing the interpolation weight for the health bar value
    static constexpr float LERP_WEIGHT = 5;

    // Variables storing position and size of health bar
    sf::Vector2f position, size;

    // Variable storing colour of health bar
    sf::Color fillColour;

    // Variables storing health values
    float maxValue, value, destValue;

};

#endif