#ifndef PLAYER_SHIP_HPP
#define PLAYER_SHIP_HPP

#include <cmath>

#include <SFML/Graphics.hpp>

#include "Constants.hpp"
#include "TextureManager.hpp"

class PlayerShip
{

public:
    PlayerShip();

    void update(float deltaTime, sf::Vector2i mouse_position);

    void draw(sf::RenderWindow& window);

    void setPosition(sf::Vector2f new_position);
    sf::Vector2f getPosition();

private:
    const float SPEED = 200;

    sf::Vector2f position;
    float direction;

    sf::RectangleShape rect;
};

#endif