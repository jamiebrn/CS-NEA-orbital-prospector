#include "Objects/HealthBar.hpp"

HealthBar::HealthBar(sf::Vector2f position, sf::Vector2f size, float maxValue)
{
    this->position = position;
    this->size = size;

    this->maxValue = maxValue;
    value = maxValue;
}

void HealthBar::updateValue(float value)
{
    this->value = value;
}

void HealthBar::setDrawPosition(sf::Vector2f position)
{
    this->position = position;
}

void HealthBar::draw(sf::RenderWindow& window)
{

    sf::RectangleShape border(size);
    border.setPosition(position);
    border.setFillColor(sf::Color(0, 0, 0));

    sf::RectangleShape inset(sf::Vector2f(size.x - 10, size.y - 10));
    inset.setPosition(sf::Vector2f(position.x + 5, position.y + 5));
    inset.setFillColor(sf::Color(30, 30, 30));

    float healthWidth = (size.x - 10) * (value / maxValue);
    sf::RectangleShape health(sf::Vector2f(healthWidth, size.y - 10));
    health.setPosition(sf::Vector2f(position.x + 5, position.y + 5));
    health.setFillColor(sf::Color(30, 200, 30));

    window.draw(border);
    window.draw(inset);
    window.draw(health);

}