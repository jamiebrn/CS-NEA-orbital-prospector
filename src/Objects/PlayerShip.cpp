// PlayerShip.cpp

#include "Objects/PlayerShip.hpp"

// Constructor taking in position as parameter
PlayerShip::PlayerShip(sf::Vector2f position)
{
    // Set position from parameter
    this->position = position;

    // Initialise velocity and direction
    velocity = sf::Vector2f(0, 0);
    direction = 0;

    // Initialise health to max
    health = UpgradeManager::getHealthAmount();

    // Initialise shooting variables
    shootCooldown = 0;
    currentGunIndex = 0;

    // Initialise engine animation variables
    engineAnimationIndex = 0;
    engineAnimTick = 0;

    // Initialise engine active variable to false
    engineActive = false;

    // Initialise flash time variable
    flashTime = 0;

}

// Update player ship object position and rotation based on inputs
void PlayerShip::update(float deltaTime, sf::Vector2f mouse_position)
{

    // Movement

    // Get draw offset
    sf::Vector2f drawOffset = Camera::getDrawOffset();

    // Calculate angle between player ship and mouse
    float toMouseAngle = std::atan2(mouse_position.y - position.y - drawOffset.y, mouse_position.x - position.x - drawOffset.x);

    // Calculate rotation
    sf::Angle destination_direction = sf::radians(toMouseAngle) + sf::degrees(90);
    sf::Angle current_direction = Helper::lerpAngle(sf::radians(direction), destination_direction, ROTATION_LERP_WEIGHT * deltaTime);

    // Update rotation
    direction = current_direction.asRadians();

    // If left mouse button is pressed, move forwards
    if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
    {
        // Calculate velocity direction vector
        sf::Vector2f directionVector = sf::Vector2f(0, -1);
        directionVector = directionVector.rotatedBy(sf::radians(direction));

        // Accelerate towards max velocity
        velocity.x = Helper::lerp(velocity.x, directionVector.x * MAX_VELOCITY * UpgradeManager::getSpeedAmount(), ACCELERATION * deltaTime);
        velocity.y = Helper::lerp(velocity.y, directionVector.y * MAX_VELOCITY * UpgradeManager::getSpeedAmount(), ACCELERATION * deltaTime);

        // Set engine active to true, as ship is accelerating
        engineActive = true;
    }
    // Decelerate if left mouse button is not pressed
    else
    {
        // Decelerate velocity to 0
        velocity.x = Helper::lerp(velocity.x, 0, DECELERATION * deltaTime);
        velocity.y = Helper::lerp(velocity.y, 0, DECELERATION * deltaTime);

        // Set engine active to false, as ship is not accelerating
        engineActive = false;
    }

    // If player ship is alive, update as normal
    if (isAlive())
    {
        // Update position using calculated velocity
        position += velocity * deltaTime;

        // Regenerate health if required
        health = std::min(health + deltaTime, static_cast<float>(UpgradeManager::getHealthAmount()));

        // Enemy bullet collision
        // Iterate over all enemy bullets and check for collision
        for (Bullet& bullet : BulletManager::getEnemyBullets())
        {
            // Calculate square distance to enemy ship bullet
            float lengthSq = (position - bullet.getPosition()).lengthSq();
            // If enemy ship bullet is within hitbox range, damage ship and kill bullet
            if (lengthSq <= HITBOX_RADIUS * HITBOX_RADIUS)
            {
                damage(1);
                bullet.kill();
            }
        }

        // Shooting
        // Update shoot cooldown timer
        shootCooldown += deltaTime;

        // If right mouse button is pressed, and shoot cooldown time is over, shoot bullet
        if (sf::Mouse::isButtonPressed(sf::Mouse::Right) && shootCooldown >= SHOOT_COOLDOWN)
        {
            // Reset shoot cooldown
            shootCooldown = 0;
            // Shoot bullet
            shootBullets();

            // Increment gun index, so the current gun is shot from when next bullet spawns
            currentGunIndex = (currentGunIndex + 1) % bulletSpawnPos.size();
        }

        // Item pickups
        // Get a vector containing all items being picked up by the player
        std::vector<ItemPickupType> pickedUp = ItemPickupManager::testCollectedPickups(position, ITEM_PICKUP_RADIUS);

        // Iterate over all items picked up
        for (ItemPickupType item : pickedUp)
        {
            // Add item to inventory
            InventoryManager::addItem(item, 1);
            // Add experience
            InventoryManager::addExperience(InventoryManager::itemPrice(item));
            // Add to item collection mission goal
            MissionManager::addToGoal(MissionType::Collect, 1);
        }

        // If picked up any items, play pickup sound
        if (pickedUp.size() > 0)
        {
            SoundManager::playSound(SoundType::ItemPickup);
        }

    }
    // If player ship is dead, update in dead state
    else
    {
        // When dead
        // Decrement respawn timer
        respawnCount -= deltaTime;
        
        // If respawn timer is over, respawn
        if (respawnCount <= 0)
        {
            respawn();
        }
    }

    // Animation
    // If the engine is active, update animation
    if (engineActive)
    {
        // Increment animation timer
        engineAnimTick += deltaTime;
        // Increment engine animation frame if timer is over
        if (engineAnimTick >= ENGINE_ANIM_TICK_MAX)
        {
            engineAnimTick = 0;
            engineAnimationIndex = (engineAnimationIndex + 1) % 10;
        }
    }

    // Decrement flash time animation variable
    flashTime -= deltaTime;

}

// Respawn
void PlayerShip::respawn()
{
    // Reset position
    position = sf::Vector2f(5000, 5000);
    // Reset health to max
    health = UpgradeManager::getHealthAmount();
}

// Damage player ship by amount
void PlayerShip::damage(int amount)
{
    // If player ship is not alive, do not attempt to damage
    if (!isAlive())
        return;
    
    // Decrease health by amount damaged
    health -= amount;

    // Reset flash time timer variable, as player has been damaged
    flashTime = FLASH_TIME_MAX;

    // If player ship not alive after being damaged, set respawn count to 5
    // Meaning player ship will enter respawn state for 5 seconds
    if (!isAlive())
    {
        respawnCount = 5;
    }

}

// Shoot bullets
void PlayerShip::shootBullets()
{
    // Get relative bullet spawn position
    sf::Vector2f localSpawnPos = bulletSpawnPos[currentGunIndex];

    // Calculate bullet spawn position in global space
    sf::Vector2f globalPosition = position;
    globalPosition += localSpawnPos.rotatedBy(sf::radians(direction)) * 4.0f;

    // Create bullet at calculated global position with rotation
    BulletManager::createBullet(globalPosition, sf::radians(direction));

    // Play bullet shoot sound
    SoundManager::playSound(SoundType::Shoot);

}

// Draw player ship
void PlayerShip::draw(sf::RenderWindow& window)
{
    // If player ship is not alive, do not draw it
    if (!isAlive())
        return;
    
    // Get draw offset
    sf::Vector2f drawOffset = Camera::getDrawOffset();

    // Draw engine trail if engine is active
    if (engineActive)
    {
        // Create engine trail animation draw data
        TextureDrawData engineDrawData = {
            TextureType::PlayerShipEngine,
            position + drawOffset,
            sf::radians(direction),
            4
        };

        // Calculate frame to draw from engine animation spritesheet
        sf::IntRect engineSubRect = sf::IntRect(sf::Vector2i(64 * engineAnimationIndex, 0), sf::Vector2i(64, 64));

        // Draw engine trail sprite with draw data and calculate frame
        TextureManager::drawSubTexture(window, engineDrawData, engineSubRect);
    }


    // Draw ship
    // Create draw data
    TextureDrawData shipDrawData = {
        TextureType::PlayerShip,
        position + drawOffset,
        sf::radians(direction),
        4
    };

    // Draw player ship sprite
    TextureManager::drawTexture(window, shipDrawData);

    // Draw flash effect from being damaged if flash time is greater than 0
    if (flashTime > 0)
    {
        // Calculate flash sprite alpha
        float flashAlpha = (flashTime / FLASH_TIME_MAX) * 210;

        // Create draw data using calculate alpha
        TextureDrawData flashDrawData = {
            TextureType::PlayerShipFlash,
            position + drawOffset,
            sf::radians(direction),
            4,
            true,
            sf::Color(255, 255, 255, flashAlpha)
        };

        // Draw flash sprite
        TextureManager::drawTexture(window, flashDrawData);
    }

}

// Set player ship position
void PlayerShip::setPosition(sf::Vector2f new_position)
{
    position = new_position;
}

// Get player ship position
sf::Vector2f PlayerShip::getPosition() const
{
    return position;
}