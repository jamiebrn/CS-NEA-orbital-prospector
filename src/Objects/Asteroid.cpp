// Asteroid.cpp

#include "Objects/Asteroid.hpp"

// Constructor, taking in a position for the asteroid
Asteroid::Asteroid(sf::Vector2f position)
{
    // Set asteroid position from parameter
    this->position = position;

    // Randomise rotation
    rotation = sf::degrees(rand() % 360);

    // Randomise asteroid scale between 4.5 and 6.5
    scale = 4.5f + (rand() % 2);

    // Randomise asteroid depth between 0.8 and 2.2
    depth = 1.0f + (static_cast<float>(rand() % 700) / 500.0f) - 0.2f;

    // Initialise flash time variable to 0
    flashTime = 0;

    // Initialise health remaining to max health
    health = MAX_HEALTH;

    // Set whether asteroid is exploding to false
    exploding = false;

    // Set asteroid alive to true
    alive = true;
}

// Update the asteroid
void Asteroid::update(PlanetType currentPlanet, float deltaTime)
{
    // If the asteroid is not currently exploding, update as normal
    if (!exploding)
    {
        // Decrease flash time value down to a minimum of 0
        flashTime = std::max(flashTime - deltaTime, 0.0f);

        // Check bullet collision for every player ship bullet
        for (Bullet& bullet : BulletManager::getBullets())
        {
            // Get position of bullet
            sf::Vector2f bulletPos = bullet.getPosition();
            // Test collision with bullet
            if (isColliding(bulletPos))
            {
                // If colliding, damage asteroid by 1
                damage(1);
                // Kill the bullet
                bullet.kill();
            }
        }

        // Check bullet collision for every enemy ship bullet
        for (Bullet& bullet : BulletManager::getEnemyBullets())
        {
            // Get position of bullet
            sf::Vector2f bulletPos = bullet.getPosition();
            // Test collision with bullet
            if (isColliding(bulletPos))
            {
                // If colliding, damage asteroid by 1
                damage(1);
                // Kill the bullet
                bullet.kill();
            }
        }
        
        // Finish updating asteroid
        return;
    }

    // When exploding

    // Increment time since last explosion frame change
    explosionFrameTick += deltaTime;

    // If time since last frame change reaches time each frame should take, increment frame
    if (explosionFrameTick >= EXPLOSION_FRAME_MAX_TICK)
    {
        // Reset time since last explosion frame change
        explosionFrameTick = 0;
        // Increment explosion animation frame
        explosionFrame++;
        // If explosion animation is finished, destroy asteroid
        if (explosionFrame >= EXPLOSION_FRAMES)
        {
            // Spawn item pickups
            spawnPickups(currentPlanet);
            // Set asteroid alive value to false
            alive = false;
        }
    }

}

// Spawn item pickups when asteroid is destroyed
void Asteroid::spawnPickups(PlanetType currentPlanet)
{
    // Randomise amount of item drops from 1-3
    int pickupCount = rand() % 3;

    // Spawn amount of item drops
    for (int i = 0; i <= pickupCount; i++)
    {
        // Calculate radius of asteroid
        int radius = (18 * scale) / depth;

        // Randomise an amount of distance away from asteroid centre
        float projection = rand() % radius;

        // Randomise the rotation to spawn the item pickup about the asteroid centre
        sf::Angle rotation = sf::degrees(rand() % 360);

        // Calculate the spawn position of the item pickup relative to the asteroid centre
        sf::Vector2f spawnPos = sf::Vector2f(0, -1).rotatedBy(rotation) * projection;

        // Add the asteroid position (normalised to standard depth) to get position in global space
        spawnPos += getNormalisedPosition();

        // Create variable storing a type of item pickup
        ItemPickupType pickupType;

        // Randomly select a float value from 0-1, to represent the type of item that will drop
        float typeRand = static_cast<float>((rand() % 101)) / 100.0f;

        // Store the total chance of items iterated over
        float cumulativeChance = 0.0f;

        // Iterate over all possible asteroid drops with respective drop rates on the current planet
        for (std::pair<ItemPickupType, float> pickupChance : asteroidDropRates.at(currentPlanet))
        {
            // Add the drop chance of the current item iterating over to the total chance
            cumulativeChance += pickupChance.second;

            // If the randomly selected value is smaller than or equal to total chance calculated,
            // select this type of item to spawn
            if (typeRand <= cumulativeChance)
            {
                // Spawn item of randomly chosen type at calculated position
                ItemPickupManager::addItem(pickupChance.first, spawnPos);
                // End iteration of possible item drops, as item has spawned
                break;
            }
        }

    }
}

// Test whether the asteroid is colliding with a bullet at a given position
bool Asteroid::isColliding(sf::Vector2f bulletTip)
{
    // If asteroid is currently exploding, do not attempt collision with it
    if (exploding)
        return false;

    // Calculate square distance from asteroid centre to bullet
    float distanceSq = (getNormalisedPosition() - bulletTip).lengthSq();

    // Calculate radius of asteroid
    float radius = 18 * scale;

    // If square distance from asteroid centre to bullet is smaller than square radius,
    // return true, meaning bullet is colliding
    if (distanceSq < radius * radius)
    {
        return true;
    }

    // Return false by default (no collision)
    return false;

}

// Damage asteroid by amount
void Asteroid::damage(int amount)
{
    // Set flash time value to maximum flash time, as asteroid has just been damaged
    flashTime = FLASH_TIME;

    // Decrease health by damaged amount
    health -= amount;

    // If health is 0 or smaller, destroy asteroid
    if (health <= 0)
    {
        // Set exploding to true, as asteroid is being destroyed
        exploding = true;
        // Reset explosion animation values
        explosionFrame = 0;
        explosionFrameTick = 0;

        // Play asteroid explosion sound effect
        SoundManager::playSound(SoundType::AsteroidExplode);
    }

}

// Draw the asteroid
void Asteroid::draw(sf::RenderWindow& window)
{

    // If not exploding, draw asteroid normally
    if (!exploding)
    {
        drawAsteroid(window);
    }
    // If exploding, draw asteroid exploding
    else
    {
        drawExplosion(window);
    }

}

// Draw asteroid in standard alive state
void Asteroid::drawAsteroid(sf::RenderWindow& window)
{
    // If asteroid is not in the player view, do not draw it (reduces unnecessary draw calls)
    if (!Camera::isInView(getNormalisedPosition(), sf::Vector2f(200, 200)))
        return;

    // Get camera draw offset
    sf::Vector2f drawOffset = Camera::getDrawOffset();
    
    // Create draw data for asteroid sprite with asteroid values
    TextureDrawData drawData = {
        TextureType::AsteroidCrack,
        position + drawOffset / depth,
        rotation,
        scale
    };

    // Calculate asteroid crack animation frame
    int subCrackFrames = static_cast<int>((float)(CRACK_FRAMES - 1) * ((float)health / (float)MAX_HEALTH));
    int crackFrame = CRACK_FRAMES - subCrackFrames - 1;

    // Calculate area of asteroid crack sprite sheet to draw from
    sf::IntRect subRect(sf::Vector2i(crackFrame * 96, 0), sf::Vector2i(96, 96));

    // Draw asteroid sprite using draw data and correct frame
    TextureManager::drawSubTexture(window, drawData, subRect);

    // If asteroid flash time is greater than 0, white flash should be drawn
    if (flashTime > 0)
    {
        // Calculate alpha of asteroid flash
        float flashAlpha = 210.0f * (flashTime / FLASH_TIME);

        // Create draw data for asteroid flash sprite with calculated alpha
        drawData = {
            TextureType::AsteroidFlash,
            position + drawOffset / depth,
            rotation,
            scale,
            true,
            sf::Color(255, 255, 255, flashAlpha)
        };

        // Draw asteroid flash sprite
        TextureManager::drawTexture(window, drawData);
    }

}

// Draw asteroid in explosion animation state
void Asteroid::drawExplosion(sf::RenderWindow& window)
{
    // Get camera draw offset
    sf::Vector2f drawOffset = Camera::getDrawOffset();

    // Create draw data for asteroid explosion sprite
    TextureDrawData drawData = {
        TextureType::AsteroidExplode,
        position + drawOffset / depth,
        rotation,
        scale
    };

    // Calculate area from asteroid explosion sprite sheet to draw from
    sf::IntRect subRect(sf::Vector2i(explosionFrame * 96, 0), sf::Vector2i(96, 96));

    // Draw asteroid explosion sprite using draw data and correct frame
    TextureManager::drawSubTexture(window, drawData, subRect);

}

// Return whether the asteroid has any health remaining
bool Asteroid::isAlive()
{
    // Return alive variable
    return alive;
}

// Get position, reverted back to standard depth level (is drawn at different "depth", so standard position will be incorrect)
sf::Vector2f Asteroid::getNormalisedPosition()
{
    // Get camera draw offset
    sf::Vector2f drawOffset = Camera::getDrawOffset();

    // Calculate depth normalised position by utilising the unproject depth function
    sf::Vector2f normalisedPosition = position + drawOffset * Helper::unprojectDepthMultiplier(depth, 1);

    // Return the calculated normalise position
    return normalisedPosition;

}

// Create an asteroid data object which represents this asteroid
AsteroidData Asteroid::generateData()
{
    // Create asteroid data object
    AsteroidData data;

    // Assign asteroid values to asteroid data object
    data.x = position.x;
    data.y = position.y;
    data.rot = rotation.asDegrees();
    data.scale = scale;
    data.depth = depth;
    data.hp = health;

    // Return asteroid data object
    return data;

}

// Override the data of this asteroid with an asteroid data object
void Asteroid::setData(AsteroidData data)
{
    // Override asteroid values from asteroid data
    position = sf::Vector2f(data.x, data.y);
    rotation = sf::degrees(data.rot);
    scale = data.scale;
    depth = data.depth;
    health = data.hp;
}