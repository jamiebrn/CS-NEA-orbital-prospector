#ifndef ENEMY_SHIP_HPP
#define ENEMY_SHIP_HPP

#include <SFML/Graphics.hpp>

#include "DrawableObject.hpp"
#include "Camera.hpp"
#include "Helper.hpp"
#include "Manager/TextureManager.hpp"
#include "Objects/HealthBar.hpp"

class EnemyShip : public DrawableObject
{

public:
    EnemyShip(sf::Vector2f position);

    void update(sf::Vector2f playerPos, float deltaTime);

    void draw(sf::RenderWindow& window) override;

    bool isBulletColliding(sf::Vector2f bulletPos);

    bool isAlive();

    sf::Vector2f getPosition() const;

private:
    void damage(int amount);

private:
    const float SCALE = 6;

    const float SPEED = 100;
    const float ACCELERATION = 6;
    const float DECELERATION = 8;

    const int MAX_HEALTH = 20;

    const float ROTATION_LERP_WEIGHT = 4;

    const float PLAYER_SHOOT_RADIUS = 350;

    const float HITBOX_RADIUS = 5 * SCALE;

    const int ENGINE_ANIM_FRAMES = 10;
    const float ENGINE_ANIM_TICK_MAX = 0.06;

    const float MAX_FLASH_TIME = 0.2;

    sf::Vector2f position, velocity;
    sf::Angle rotation;

    int health;
    HealthBar healthBar;

    sf::Vector2f hitboxPosition;

    bool engineActive;
    float engineFrameTick;
    int engineFrameIndex;

    float flashTime;

};

#endif