// EnemyShip.cpp

#include "Objects/EnemyShip.hpp"

// Constructor taking in a position
EnemyShip::EnemyShip(sf::Vector2f position)
    : healthBar(sf::Vector2f(0, 0), sf::Vector2f(100, 30), MAX_HEALTH) // initialise health bar object
{
    // Set position from parameter
    this->position = position;

    // Initialise velocity and rotation
    velocity = sf::Vector2f(0, 0);
    rotation = sf::degrees(0);

    // Initialise behaviour state to patrol and randomise patrol target position
    behaviourState = EnemyShipBehaviourState::Patrol;
    randomisePatrolTarget();

    // Set ID to time since Jan 1 1970 in ms
    id = std::chrono::system_clock::now().time_since_epoch() / std::chrono::milliseconds(1);

    // Reset shoot cooldown timer
    shootCooldown = 0;

    // Initialise hitbox position
    hitboxPosition = sf::Vector2f(0, 0);

    // Randomise engine animation frame and reset frame timer to 0
    engineFrameIndex = rand() % ENGINE_ANIM_FRAMES;
    engineFrameTick = 0;

    // Initialise destroyed animation variables
    destroyedFrameTick = 0;
    destroyedFrameIndex = 0;

    // Set engine active to false
    engineActive = false;

    // Initialise flash time variable to 0
    flashTime = 0;

    // Set health remaining equal to max health
    health = MAX_HEALTH;

    // Update health bar value to current health
    healthBar.updateValue(health);

}

// Constructor taking in an enemy ship data object
EnemyShip::EnemyShip(EnemyShipData data)
    : healthBar(sf::Vector2f(0, 0), sf::Vector2f(100, 30), MAX_HEALTH) // initialise health bar object
{

    // Load values from enemy ship data object
    position = sf::Vector2f(data.x, data.y);
    velocity = sf::Vector2f(data.velx, data.vely);
    rotation = sf::degrees(data.rot);
    health = data.hp;
    behaviourState = data.behaviourState;
    id = data.id;

    // Reset shoot cooldown timer
    shootCooldown = 0;

    // Initialise hitbox position
    hitboxPosition = sf::Vector2f(0, 0);

    // Randomise engine animation frame and reset frame timer to 0
    engineFrameIndex = rand() % ENGINE_ANIM_FRAMES;
    engineFrameTick = 0;

    // Initialise destroyed animation variables
    destroyedFrameTick = 0;
    destroyedFrameIndex = 0;

    // Set engine active to false
    engineActive = false;

    // Initialise flash time variable to 0
    flashTime = 0;

    // Update health bar value to current health
    healthBar.updateValue(health);

}

// Update enemy ship
void EnemyShip::update(const PlayerShip& playerShip, const std::vector<EnemyShip>& ships, float deltaTime)
{
    // If enemy ship is alive, update normally
    if (isAlive())
    {

        // Update based on behaviour state
        switch (behaviourState)
        {
            // Update enemy ship in patrol state
            case EnemyShipBehaviourState::Patrol:
                updatePatrol(playerShip, deltaTime);
                break;
            
            // Update enemy ship in target item state
            case EnemyShipBehaviourState::TargetItem:
                updateTargetItem(playerShip, deltaTime);
                break;
            
            // Update enemy ship in target player state
            case EnemyShipBehaviourState::TargetPlayer:
                updateTargetPlayer(playerShip, deltaTime);
                break;
            
            // Update enemy ship in attack player state
            case EnemyShipBehaviourState::AttackPlayer:
                updateAttackPlayer(playerShip, deltaTime);
                break;
            
            // Update enemy ship in flee player state
            case EnemyShipBehaviourState::FleePlayer:
                updateFleePlayer(playerShip, deltaTime);
                break;
        }

        // If engine is active, update engine animation
        if (engineActive)
        {
            // Increment time since last engine animation frame change
            engineFrameTick += deltaTime;
            // Increment engine animation frame if time has passed
            if (engineFrameTick >= ENGINE_ANIM_TICK_MAX)
            {
                engineFrameTick = 0;
                engineFrameIndex = (engineFrameIndex + 1) % ENGINE_ANIM_FRAMES;
            }
        }

        // Check bullet collision for player ship bullets
        for (Bullet& bullet : BulletManager::getBullets())
        {
            // Get bullet position
            sf::Vector2f bulletPos = bullet.getPosition();
            // If bullet is colliding with enemy ship
            if (isBulletColliding(bulletPos))
            {
                // Damage enemy ship
                damage(1, playerShip);
                // Destroy bullet
                bullet.kill();
            }
        }

    }
    // If not alive, update in destroyed state
    else
    {
        // Update destroyed ship animation
        destroyedFrameTick += deltaTime;
        // Increment destroyed frame animation if time has passed
        if (destroyedFrameTick >= DESTROYED_ANIM_TICK_MAX)
        {
            destroyedFrameTick = 0;
            destroyedFrameIndex++;
        }
    }

    // Avoid (collide with) other enemy ships
    avoidOtherShips(ships);
    
    // Update variables

    // Update position
    position += velocity * deltaTime;

    // Update hitbox position
    sf::Vector2f hitboxOffset = -sf::Vector2f(0, -1).rotatedBy(rotation) * 2.0f * SCALE;
    hitboxPosition = position + hitboxOffset;

    // Update flash time
    flashTime = std::max(flashTime - deltaTime, 0.0f);

    // Update shoot cooldown
    shootCooldown = std::max(shootCooldown - deltaTime, 0.0f);

    // Update health bar
    healthBar.update(deltaTime);

}

// Update in patrol state
void EnemyShip::updatePatrol(const PlayerShip& playerShip, float deltaTime)
{
    // State switching

    // If health is under 20%, switch to flee player state
    if (static_cast<float>(health) / MAX_HEALTH < 0.2)
        behaviourState = EnemyShipBehaviourState::FleePlayer;
    
    // Iterate over all item pickups and check if close enough to target
    for (ItemPickup item : ItemPickupManager::getPickups())
    {
        // If close enough to target item pickup
        if ((item.getPosition() - position).lengthSq() <= 1500 * 1500)
        {
            // Set patrol target to item pickup position
            patrolTarget = item.getPosition();
            // Switch to target item state
            behaviourState = EnemyShipBehaviourState::TargetItem;
        }
    }

    // If within close enough range of player (and player is alive), target player
    if (playerShip.isAlive() && (position - playerShip.getPosition()).lengthSq() <= 800 * 800)
    {
        // Switch to target player state
        behaviourState = EnemyShipBehaviourState::TargetPlayer;
    }

    // Patrol state updating

    // Calculate rotation of enemy ship to face towards patrol target
    sf::Angle destRotation = (position - patrolTarget).angle();
    // Update rotation to point towards calulcated rotation
    rotation = Helper::lerpAngle(rotation, destRotation, ROTATION_LERP_WEIGHT * deltaTime);

    // Calculate velocity based on speed and rotation
    velocity = sf::Vector2f(-1, 0).rotatedBy(rotation) * SPEED;

    // If the patrol target has been reached, generate a new patrol target
    if ((position - patrolTarget).lengthSq() < 100)
        randomisePatrolTarget();

    // Set engine active to true, as ship is moving
    engineActive = true;
}

// Randomise the enemy ship patrol target
void EnemyShip::randomisePatrolTarget()
{
    // Randomise patrol target posiion to random world position
    patrolTarget.x = rand() % static_cast<int>(WORLD_WIDTH);
    patrolTarget.y = rand() % static_cast<int>(WORLD_HEIGHT);
}

// Update in target item state
void EnemyShip::updateTargetItem(const PlayerShip& playerShip, float deltaTime)
{
    // State switching

    // If health is below 20%, switch to flee player state
    if (static_cast<float>(health) / MAX_HEALTH < 0.2)
        behaviourState = EnemyShipBehaviourState::FleePlayer;

    // If within close enough range to player ship, switch to target player state
    if ((position - playerShip.getPosition()).lengthSq() <= 800 * 800)
    {
        // Switch to target player state
        behaviourState = EnemyShipBehaviourState::TargetPlayer;
    }

    // If reached target position (which would be the position of an item in this case)
    // switch back to patrol state and generate a new patrol target position
    if ((position - patrolTarget).lengthSq() < 100)
    {
        behaviourState = EnemyShipBehaviourState::Patrol;
        randomisePatrolTarget();
    }

    // Target item state updating

    // Calculate rotation of enemy ship to face towards patrol target
    sf::Angle destRotation = (position - patrolTarget).angle();
    // Update rotation to point towards calulcated rotation
    rotation = Helper::lerpAngle(rotation, destRotation, ROTATION_LERP_WEIGHT * deltaTime);

    // Calculate velocity based on speed and rotation
    velocity = sf::Vector2f(-1, 0).rotatedBy(rotation) * SPEED;

    // Collect any item pickups within range
    ItemPickupManager::testCollectedPickups(position, 20);

    // Set engine active to true, as ship is moving
    engineActive = true;
}

void EnemyShip::updateTargetPlayer(const PlayerShip& playerShip, float deltaTime)
{
    // State switching

    // If health is below 20%, switch to flee player state
    if (static_cast<float>(health) / MAX_HEALTH < 0.2)
        behaviourState = EnemyShipBehaviourState::FleePlayer;

    // Calculate square distance to player ship
    float playerDistSq = (position - playerShip.getPosition()).lengthSq();

    // If no longer within player ship range, switch back to patrol state and generate new patrol target position
    if (playerDistSq > 800 * 800)
    {
        behaviourState = EnemyShipBehaviourState::Patrol;
        randomisePatrolTarget();
    }

    // If close enough to player ship, switch to attack player state
    if (playerDistSq <= 600 * 600)
    {
        behaviourState = EnemyShipBehaviourState::AttackPlayer;
    }

    // If player is no longer alive, switch back to patrol state
    if (!playerShip.isAlive())
        behaviourState = EnemyShipBehaviourState::Patrol;
    
    // Target player state updating
    
    // Calculate rotation of enemy ship to face towards patrol target
    sf::Angle destRotation = (position - playerShip.getPosition()).angle();
    // Update rotation to point towards calulcated rotation
    rotation = Helper::lerpAngle(rotation, destRotation, ROTATION_LERP_WEIGHT * deltaTime);

    // Calculate velocity based on speed and rotation
    velocity = sf::Vector2f(-1, 0).rotatedBy(rotation) * SPEED;

}

void EnemyShip::updateAttackPlayer(const PlayerShip& playerShip, float deltaTime)
{
    // State switching

    // If health is below 20%, switch to flee player state
    if (static_cast<float>(health) / MAX_HEALTH < 0.2)
        behaviourState = EnemyShipBehaviourState::FleePlayer;

    // If no longer within close enough range to player ship, switch to target player state
    if ((position - playerShip.getPosition()).lengthSq() > 600 * 600)
    {
        behaviourState = EnemyShipBehaviourState::TargetPlayer;
    }

    // If player ship is no longer alive, switch to patrol state
    if (!playerShip.isAlive())
        behaviourState = EnemyShipBehaviourState::Patrol;
    
    // Attack player state updating

    // Calculate rotation of enemy ship to face towards patrol target
    sf::Angle destRotation = (position - playerShip.getPosition()).angle();
    // Update rotation to point towards calulcated rotation
    rotation = Helper::lerpAngle(rotation, destRotation, ROTATION_LERP_WEIGHT * 1.2f * deltaTime);

    // Calculate velocity based on speed and rotation
    velocity = sf::Vector2f(-1, 0).rotatedBy(rotation) * SPEED * 1.4f;

    // Shoot if shoot cooldown has finished
    if (shootCooldown <= 0)
    {
        shootCooldown = SHOOT_COOLDOWN;
        shoot();
    }

}

// Update in flee player state
void EnemyShip::updateFleePlayer(const PlayerShip& playerShip, float deltaTime)
{
    // State switching

    // If health has regenerated back up to at least 50%, switch to patrol state and generate new patrol target position
    if (static_cast<float>(health) / MAX_HEALTH >= 0.5)
    {
        behaviourState = EnemyShipBehaviourState::Patrol;
        randomisePatrolTarget();
    }

    // Flee player state updating

    // Calculate rotation of enemy ship to face towards patrol target
    sf::Angle destRotation = (playerShip.getPosition() - position).angle();
    // Update rotation to point towards calulcated rotation
    rotation = Helper::lerpAngle(rotation, destRotation, ROTATION_LERP_WEIGHT * deltaTime);

    // Calculate velocity based on speed and rotation
    velocity = sf::Vector2f(-1, 0).rotatedBy(rotation) * SPEED * 2.0f;

    // Regenerate health
    health = std::min(health + deltaTime, static_cast<float>(MAX_HEALTH));

    // Update health bar with new health value
    healthBar.updateValue(health);
}

// Test collision with and avoid other enemy ships
void EnemyShip::avoidOtherShips(const std::vector<EnemyShip>& ships)
{
    // Move away from other closeby ships

    // Variable storing whether a close ship in range has been found
    bool closeShipProximity = false;
    // If a close ship has been found, its position will be stored in this variable
    sf::Vector2f closeShipPos;

    // Iterate over all enemy ships
    for (const EnemyShip& ship : ships)
    {

        // Skip self (do not want to attempt to avoid/collide with self)
        if (id == ship.getID())
            continue;
        
        // Get position of enemy ship
        sf::Vector2f shipPos = ship.getPosition();

        // Calculate square distance to enemy ship
        float distanceSq = (position - shipPos).lengthSq();

        // If distance is within ship closest range constant, move away from ship
        if(distanceSq <= SHIP_CLOSEST_RADIUS * SHIP_CLOSEST_RADIUS * SCALE)
        {
            // Not already found close ship, so set close ship position to this ship position
            if (!closeShipProximity)
            {
                closeShipPos = shipPos;
                closeShipProximity = true;
            }
            // Already have a close ship position, so compare to store the closest
            else
            {
                // Calculate square distance of ship already found
                float closestDistanceSq = (position - closeShipPos).lengthSq();
                // If this ship is closer, override the close ship position with this ship's position
                if (distanceSq < closestDistanceSq)
                {
                    closeShipPos = shipPos;
                }
            }

        }

    }

    // If a close ship was found, move away from it
    if (closeShipProximity)
    {
        // Calculate a new velocity to "push" this ship away from the one found
        float velocityMagnitude = velocity.length();
        float distanceSq = (position - closeShipPos).lengthSq();
        float pushMult = 1 - (distanceSq / (SHIP_CLOSEST_RADIUS * SHIP_CLOSEST_RADIUS * SCALE));

        // Calculate vector to "push" the ship
        sf::Vector2f pushVector = (position - closeShipPos).normalized() * velocityMagnitude;

        // Apply the push vector to the velocity
        velocity += pushMult * pushVector;

        // Ensure velocity magnitude remains constant throughout the push
        velocity = velocity.normalized() * velocityMagnitude;
    }

}

// Test collision with player ship bullets
bool EnemyShip::isBulletColliding(sf::Vector2f bulletPos)
{
    // Calculate square distance to bullet
    float distanceSq = (hitboxPosition - bulletPos).lengthSq();

    // If square distance to bullet is within square hitbox radius, return true (collision found)
    if (distanceSq < HITBOX_RADIUS * HITBOX_RADIUS * SCALE)
    {
        return true;
    }

    // Return false by default (no collision)
    return false;

}

// Shoot bullet
void EnemyShip::shoot()
{
    // Calculate offset from enemy ship to spawn bullet at
    sf::Vector2f offset = sf::Vector2f(-6 * SCALE, 0).rotatedBy(rotation);

    // Spawn bullet at position with rotation
    BulletManager::createEnemyBullet(position + offset, rotation - sf::degrees(90));

    // Play enemy ship shooting sound
    SoundManager::playSound(SoundType::EnemyShoot);
}

// Damage enemy ship by amount
void EnemyShip::damage(int amount, const PlayerShip& playerShip)
{
    // If ship is not alive, do not attempt to damage it
    if (!isAlive())
        return;
    
    // Set flash time to max
    flashTime = MAX_FLASH_TIME;

    // Decrease health by amount damaged
    health -= amount;

    // Set patrol target to player ship (damaged by player, so must go towards player)
    patrolTarget = playerShip.getPosition();

    // If is still alive after being damaged, update health bar
    if (isAlive())
        healthBar.updateValue(health);
    // If not, kill the ship
    else
    {
        // Add player experience
        InventoryManager::addExperience(15);
        // Add to mission goal
        MissionManager::addToGoal(MissionType::Kill, 1);
        // Play ship explosion sound
        SoundManager::playSound(SoundType::ShipExplode);
    }
}

// Returns whether any health is remaining
bool EnemyShip::isAlive()
{
    return (health > 0);
}

// Returns whether destroyed animation is finished
bool EnemyShip::isDestroyed()
{
    return (destroyedFrameIndex >= DESTROYED_ANIM_FRAMES - 1);
}

// Returns whether the enemy ship can be freed from memory
bool EnemyShip::canRemove()
{
    return (!isAlive() && isDestroyed());
}

// Create enemy ship data object from enemy ship
EnemyShipData EnemyShip::generateData()
{
    // Create enemy ship data object
    EnemyShipData data;

    // Store enemy ship values in enemy ship data object
    data.x = position.x;
    data.y = position.y;
    data.velx = velocity.x;
    data.vely = velocity.y;
    data.rot = rotation.asDegrees();
    data.hp = health;
    data.id = id;
    data.behaviourState = behaviourState;

    // Return enemy ship data object
    return data;
}

// Draw enemy ship
void EnemyShip::draw(sf::RenderWindow& window)
{
    // If enemy ship is alive, draw in alive state
    if (isAlive())
    {
        drawAlive(window);
    }
    // If not, draw in destroyed state
    else
    {
        drawDestroyed(window);
    }
}

// Draw enemy ship in alive state
void EnemyShip::drawAlive(sf::RenderWindow& window)
{
    // If enemy ship not in player view, do not draw it
    if (!Camera::isInView(position, sf::Vector2f(150, 150)))
        return;
    
    // Get camera draw offset
    sf::Vector2f drawOffset = Camera::getDrawOffset();

    // If engine is active, draw engine animation
    if (engineActive)
    {
        // Create engine animation draw data
        TextureDrawData engineDrawData = {
            TextureType::EnemyShipEngine,
            position + drawOffset,
            rotation - sf::degrees(90),
            SCALE
        };

        // Calculate frame to draw
        sf::IntRect engineSubRect = sf::IntRect(sf::Vector2i(64 * engineFrameIndex, 0), sf::Vector2i(64, 64));

        // Draw engine animation sprite with correct frame
        TextureManager::drawSubTexture(window, engineDrawData, engineSubRect);
    }

    // Create draw data for enemy ship
    TextureDrawData drawData = {
        TextureType::EnemyShip,
        position + drawOffset,
        rotation - sf::degrees(90),
        SCALE
    };

    // Draw enemy ship sprite
    TextureManager::drawTexture(window, drawData);

    // If flash time is greater than 0, draw flash sprite
    if (flashTime > 0)
    {
        // Calculate flash sprite alpha value
        float flashAlpha = 210.0f * (flashTime / MAX_FLASH_TIME);

        // Create draw data for flash sprite with calculated alpha value
        drawData = {
            TextureType::EnemyShipFlash,
            position + drawOffset,
            rotation - sf::degrees(90),
            SCALE,
            true,
            sf::Color(255, 255, 255, flashAlpha)
        };

        // Draw flash sprite
        TextureManager::drawTexture(window, drawData);
    }

    // If health is less then max health, draw health bar
    if (health < MAX_HEALTH)
    {
        // Update health bar position and draw it
        healthBar.setDrawPosition(sf::Vector2f(position.x - 50, position.y - 50) + drawOffset);
        healthBar.draw(window);
    }

}

// Draw enemy ship in destroyed state
void EnemyShip::drawDestroyed(sf::RenderWindow& window)
{
    // Get camera draw offset
    sf::Vector2f drawOffset = Camera::getDrawOffset();

    // Create draw data for destroyed ship animation
    TextureDrawData destroyedDrawData = {
        TextureType::EnemyShipDestroyed,
        position + drawOffset,
        rotation - sf::degrees(90),
        SCALE
    };

    // Calculate destroyed ship animation frame
    sf::IntRect destroyedSubRect = sf::IntRect(sf::Vector2i(64 * destroyedFrameIndex, 0), sf::Vector2i(64, 64));

    // Draw destroyed ship sprite with correct frame
    TextureManager::drawSubTexture(window, destroyedDrawData, destroyedSubRect);
}

// Get position of enemy ship
sf::Vector2f EnemyShip::getPosition() const
{
    return position;
}

// Get ID of enemy ship
uint64_t EnemyShip::getID() const
{
    return id;
}