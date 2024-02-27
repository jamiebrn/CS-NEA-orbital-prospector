// HealthBar.cpp

#include "Objects/HealthBar.hpp"

// Constructor taking in position, size, and maximum value of health bar
HealthBar::HealthBar(sf::Vector2f position, sf::Vector2f size, float maxValue)
{
    // Set position and size from parameters
    this->position = position;
    this->size = size;

    // Set max value from parameter
    this->maxValue = maxValue;

    // Initialise value to 0
    value = 0;

    // Set fill colour to green by default
    fillColour = sf::Color(30, 200, 30);
}

// Update the health bar
void HealthBar::update(float deltaTime)
{
    // Update the value towards thes destination value over time
    value = Helper::lerp(value, destValue, LERP_WEIGHT * deltaTime);
}

// Update the current value of the health bar
void HealthBar::updateValue(float value)
{
    destValue = value;
}

// Set the max value of the health bar
void HealthBar::setMaxValue(float value)
{
    maxValue = value;
}

// Reset the health bar current value to 0
void HealthBar::reset()
{
    value = 0;
    destValue = 0;
}

// Set health bar draw position on screen
void HealthBar::setDrawPosition(sf::Vector2f position)
{
    this->position = position;
}

// Set the fill colour of the health bar
void HealthBar::setFillColour(sf::Color colour)
{
    fillColour = colour;
}

// Draw the health bar
void HealthBar::draw(sf::RenderWindow& window)
{
    // Create border rectangle
    sf::RectangleShape border(size);
    border.setPosition(position);
    border.setFillColor(sf::Color(0, 0, 0));

    // Create inset rectangle
    sf::RectangleShape inset(sf::Vector2f(size.x - 10, size.y - 10));
    inset.setPosition(sf::Vector2f(position.x + 5, position.y + 5));
    inset.setFillColor(sf::Color(30, 30, 30));

    // Create health fill rectangle
    float healthWidth = (size.x - 10) * (value / maxValue);
    sf::RectangleShape health(sf::Vector2f(healthWidth, size.y - 10));
    health.setPosition(sf::Vector2f(position.x + 5, position.y + 5));
    health.setFillColor(fillColour);

    // Draw rectangles to draw whole health bar
    window.draw(border);
    window.draw(inset);
    window.draw(health);

    // Calculate width of delta rectangle
    float deltaWidth = (size.x - 10) * ((destValue - value) / maxValue);

    // If delta rectangle has width, draw it
    if (std::abs(deltaWidth) >= 1)
    {
        // Create delta rectangle
        sf::RectangleShape delta(sf::Vector2f(deltaWidth, size.y - 10));
        delta.setPosition(sf::Vector2f(position.x + 5 + healthWidth, position.y + 5));
        delta.setFillColor(sf::Color(fillColour.r * 0.5, fillColour.g * 0.5, fillColour.b * 0.5));
        // Draw delta rectangle
        window.draw(delta);
    }

}