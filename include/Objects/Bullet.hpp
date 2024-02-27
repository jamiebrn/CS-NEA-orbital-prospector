// Bullet.hpp

#ifndef BULLET_HPP
#define BULLET_HPP

// Include libraries
#include <SFML/Graphics.hpp>
#include <iostream>

// Include headers
#include "Manager/TextureManager.hpp"
#include "Camera.hpp"
#include "Objects/DrawableObject.hpp"

// Declare bullet class
class Bullet : public DrawableObject
{

// Public class functions
public:
    // Bullet constructor, taking in a position and rotation
    Bullet(sf::Vector2f initPosition, sf::Angle initRotation);

    // Update the bullet
    void update(float deltaTime);

    // Draw the bullet
    void draw(sf::RenderWindow& window) override;

    // Get the bullet position
    sf::Vector2f getPosition();

    // Return whether the bullet is alive
    bool isAlive();

    // Kill the bullet
    void kill();

// Private member variables
private:
    // Constant values representing bullet animation
    static constexpr float MAX_ANIM_TICK = 0.04;
    static constexpr int MAX_ANIM_FRAMES = 4;

    // Constant values representing bullet lifetime in seconds
    static constexpr float LIFETIME = 6;

    // Constant value representing speed at which bullet travels at (pixels/s)
    static constexpr float SPEED = 1400;

    // Variables storing position, velocity and rotation of bullet
    sf::Vector2f position, velocity;
    sf::Angle rotation;

    // Variables storing information about bullet animation
    float animTick;
    int animIndex;

    // Variable storing time that bullet has existed for
    float timeAlive;

};

#endif