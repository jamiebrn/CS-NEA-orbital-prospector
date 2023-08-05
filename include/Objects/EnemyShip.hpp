#ifndef ENEMY_SHIP_HPP
#define ENEMY_SHIP_HPP

#include <SFML/Graphics.hpp>

#include "Camera.hpp"
#include "Helper.hpp"
#include "Manager/TextureManager.hpp"

class EnemyShip
{

public:
    EnemyShip(sf::Vector2f position);

    void update(sf::Vector2f playerPos, float deltaTime);

    void draw(sf::RenderWindow& window);

    sf::Vector2f getPosition() const;

private:
    const float SPEED = 100;
    const float ACCELERATION = 12;
    const float DECELERATION = 15;

    const float ROTATION_LERP_WEIGHT = 4;

    const float PLAYER_SHOOT_RADIUS = 350;

    sf::Vector2f position, velocity;
    sf::Angle rotation;

};

#endif