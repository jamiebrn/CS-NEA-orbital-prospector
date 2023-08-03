#ifndef ASTEROID_HPP
#define ASTEROID_HPP

#include <iostream>
#include <algorithm>

#include <SFML/Graphics.hpp>

#include "Camera.hpp"
#include "Manager/TextureManager.hpp"
#include "Manager/ItemPickupManager.hpp"
#include "Objects/ItemPickupType.hpp"
#include "Objects/DrawableObject.hpp"

class Asteroid : public DrawableObject
{

public:
    Asteroid(sf::Vector2f position);

    void update(float deltaTime);

    void draw(sf::RenderWindow& window) override;

    bool isColliding(sf::Vector2f bulletTip);

    bool isAlive();

private:
    void damage(int amount);

    void drawAsteroid(sf::RenderWindow& window);
    void drawExplosion(sf::RenderWindow& window);

    void spawnPickups();

private:
    static constexpr float FLASH_TIME = 0.15f;
    static const int MAX_HEALTH = 50;

    static const int CRACK_FRAMES = 5;
    static const int EXPLOSION_FRAMES = 7;
    static constexpr float EXPLOSION_FRAME_MAX_TICK = 0.07f;

    sf::Vector2f position;
    sf::Angle rotation;
    float scale;

    float flashTime;
    int health;

    bool exploding;
    int explosionFrame;
    float explosionFrameTick;

    bool alive;

};

#endif