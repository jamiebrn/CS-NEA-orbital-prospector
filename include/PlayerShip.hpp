//
// PlayerShip.hpp
// 
// All functions and data associated with player ship movement, position, rotation, etc.
//

#ifndef PLAYER_SHIP_HPP
#define PLAYER_SHIP_HPP

#include <cmath>

#include <SFML/Graphics.hpp>

#include "Constants.hpp"
#include "TextureManager.hpp"
#include "DrawableObject.hpp"

// PlayerShip class declaration
class PlayerShip : public DrawableObject
{

// Public functions
public:
    PlayerShip();

    void update(float deltaTime, sf::Vector2i mouse_position);

    void draw(sf::RenderWindow& window);

    void setPosition(sf::Vector2f new_position);
    sf::Vector2f getPosition();

// Private member variables
private:
    const float SPEED = 200;

    sf::Vector2f position, velocity;
    float direction;

};

#endif