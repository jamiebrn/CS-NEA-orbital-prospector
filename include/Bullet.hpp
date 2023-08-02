#ifndef BULLET_HPP
#define BULLET_HPP

#include <SFML/Graphics.hpp>

#include "TextureManager.hpp"
#include "Camera.hpp"

class Bullet
{

public:
    Bullet(sf::Vector2f position, sf::Angle rotation);

    void update(float deltaTime);

    void draw(sf::RenderWindow& window);

private:
    static constexpr float MAX_ANIM_TICK = 0.04;
    static const int MAX_ANIM_FRAMES = 4;

    static constexpr float SPEED = 600;

    sf::Vector2f position, velocity;
    sf::Angle rotation;

    float animTick;
    int animIndex;

};

#endif