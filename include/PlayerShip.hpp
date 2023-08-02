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
#include "Helper.hpp"
#include "Camera.hpp"
#include "BulletManager.hpp"

// PlayerShip class declaration
class PlayerShip : public DrawableObject
{

// Public functions
public:
    PlayerShip();

    void update(float deltaTime, sf::Vector2i mouse_position);

    void draw(sf::RenderWindow& window) override;

    void setPosition(sf::Vector2f new_position);
    sf::Vector2f getPosition();

// Private member variables
private:
    const float MAX_VELOCITY = 200;
    const float ACCELERATION = 11;
    const float DECELERATION = 16;

    const float SHOOT_COOLDOWN = 0.3;

    const float ROTATION_LERP_WEIGHT = 5;

    sf::Vector2f position, velocity;
    float direction;

    float shootCooldown;

    const float ENGINE_ANIM_TICK_MAX = 0.06;

    int engineAnimationIndex;
    float engineAnimTick;
    bool engineActive;

};

#endif