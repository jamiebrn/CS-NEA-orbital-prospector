#ifndef BULLET_HPP
#define BULLET_HPP

#include <SFML/Graphics.hpp>
#include <iostream>

#include "Manager/TextureManager.hpp"
#include "Camera.hpp"
#include "Objects/DrawableObject.hpp"

class Bullet : public DrawableObject
{

public:
    Bullet(sf::Vector2f initPosition, sf::Angle initRotation);

    void update(float deltaTime);

    void draw(sf::RenderWindow& window) override;

    sf::Vector2f getPosition();

    bool isAlive();

    void kill();

private:
    //void checkCollisions();

private:
    static constexpr float MAX_ANIM_TICK = 0.04;
    static constexpr int MAX_ANIM_FRAMES = 4;

    static constexpr float LIFETIME = 6;

    static constexpr float SPEED = 1400;

    sf::Vector2f position, velocity;
    sf::Angle rotation;

    float animTick;
    int animIndex;

    float timeAlive;

};

#endif