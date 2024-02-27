// Bullet.cpp

#include "Objects/Bullet.hpp"

// Bullet constructor, taking in a position and rotation
Bullet::Bullet(sf::Vector2f initPosition, sf::Angle initRotation)
{
    // Set position and rotation from parameters
    position = initPosition;
    rotation = initRotation;

    // Calculate velocity based on rotation and speed
    velocity = sf::Vector2f(0, -1).rotatedBy(rotation) * SPEED;

    // Reset time since last animation frame change
    animTick = 0;

    // Randomise initial animation frame
    animIndex = rand() % MAX_ANIM_FRAMES;

    // Initialise time alive to 0
    timeAlive = 0;
}

// Update the bullet
void Bullet::update(float deltaTime)
{
    // Update bullet position with velocity
    position += velocity * deltaTime;

    // Update bullet animation
    animTick += deltaTime;
    // If time to change animation frame, increment animation frame
    if (animTick >= MAX_ANIM_TICK)
    {
        // Reset time since last animation frame change
        animTick = 0;
        // Increment animation frame
        animIndex = (animIndex + 1) % MAX_ANIM_FRAMES;
    }
    
    // Increase bullet time alive
    timeAlive += deltaTime;

}

// Get the bullet position
sf::Vector2f Bullet::getPosition()
{
    // Return position
    return position;
}

// Return whether the bullet is alive
bool Bullet::isAlive()
{
    // Return whether bullet lifetime has ended
    return (timeAlive < LIFETIME);
}

// Kill the bullet
void Bullet::kill()
{
    // Set bullet time alive to maximum, which will kill the bullet
    timeAlive = LIFETIME;
}

// Draw the bullet
void Bullet::draw(sf::RenderWindow& window)
{
    // If bullet is not in player view, do not draw it
    if (!Camera::isInView(position, sf::Vector2f(50, 50)))
        return;

    // Get draw offset
    sf::Vector2f drawOffset = Camera::getDrawOffset();

    // Create bullet draw data with bullet values
    TextureDrawData bulletDrawData = {
        TextureType::Bullet,
        position + drawOffset,
        rotation,
        4
    };

    // Calculate frame of bullet animation
    sf::IntRect bulletSubRect = sf::IntRect(sf::Vector2i(animIndex * 4, 0), sf::Vector2i(4, 16));

    // Draw bullet sprite using draw data and animation frame
    TextureManager::drawSubTexture(window, bulletDrawData, bulletSubRect);

}