#include "Objects/EnemyShip.hpp"

EnemyShip::EnemyShip(sf::Vector2f position)
    : healthBar(sf::Vector2f(0, 0), sf::Vector2f(100, 30), MAX_HEALTH)
{

    this->position = position;

    velocity = sf::Vector2f(0, 0);
    rotation = sf::degrees(0);

    behaviourState = EnemyShipBehaviourState::Patrol;
    randomisePatrolTarget();

    id = std::chrono::system_clock::now().time_since_epoch() / std::chrono::milliseconds(1);

    shootCooldown = 0;

    hitboxPosition = sf::Vector2f(0, 0);
    engineFrameIndex = rand() % ENGINE_ANIM_FRAMES;
    engineFrameTick = 0;

    destroyedFrameTick = 0;
    destroyedFrameIndex = 0;

    engineActive = false;

    flashTime = 0;

    health = MAX_HEALTH;
    healthBar.updateValue(health);

}


EnemyShip::EnemyShip(EnemyShipData data)
    : healthBar(sf::Vector2f(0, 0), sf::Vector2f(100, 30), MAX_HEALTH)
{

    position = sf::Vector2f(data.x, data.y);
    velocity = sf::Vector2f(data.velx, data.vely);
    rotation = sf::degrees(data.rot);
    health = data.hp;

    behaviourState = data.behaviourState;

    id = data.id;

    shootCooldown = 0;

    hitboxPosition = sf::Vector2f(0, 0);
    engineFrameIndex = rand() % ENGINE_ANIM_FRAMES;
    engineFrameTick = 0;

    destroyedFrameTick = 0;
    destroyedFrameIndex = 0;

    engineActive = false;

    flashTime = 0;

    healthBar.updateValue(health);

}

// Update every frame
void EnemyShip::update(const PlayerShip& playerShip, const std::vector<EnemyShip>& ships, float deltaTime)
{

    
    if (isAlive())
    {

        // Update based on behaviour state

        switch (behaviourState)
        {
            case EnemyShipBehaviourState::Patrol:
                updatePatrol(playerShip, deltaTime);
                break;
            
            case EnemyShipBehaviourState::TargetItem:
                updateTargetItem(playerShip, deltaTime);
                break;
            
            case EnemyShipBehaviourState::TargetPlayer:
                updateTargetPlayer(playerShip, deltaTime);
                break;
            
            case EnemyShipBehaviourState::AttackPlayer:
                updateAttackPlayer(playerShip, deltaTime);
                break;
            
            case EnemyShipBehaviourState::FleePlayer:
                updateFleePlayer(playerShip, deltaTime);
                break;
        }

        // Animation

        if (engineActive)
        {
            engineFrameTick += deltaTime;
            if (engineFrameTick >= ENGINE_ANIM_TICK_MAX)
            {
                engineFrameTick = 0;
                engineFrameIndex = (engineFrameIndex + 1) % ENGINE_ANIM_FRAMES;
            }
        }

        // Check bullet collision
        for (Bullet& bullet : BulletManager::getBullets())
        {
            sf::Vector2f bulletPos = bullet.getPosition();
            if (isBulletColliding(bulletPos))
            {
                damage(1);
                bullet.kill();
            }
        }

    }
    else
    {
        destroyedFrameTick += deltaTime;
        if (destroyedFrameTick >= DESTROYED_ANIM_TICK_MAX)
        {
            destroyedFrameTick = 0;
            destroyedFrameIndex++;
        }
    }

    avoidOtherShips(ships);
    
    // Update variables

    position += velocity * deltaTime;

    sf::Vector2f hitboxOffset = -sf::Vector2f(0, -1).rotatedBy(rotation) * 2.0f * SCALE;
    hitboxPosition = position + hitboxOffset;

    flashTime = std::max(flashTime - deltaTime, 0.0f);

    healthBar.update(deltaTime);

}

void EnemyShip::updatePatrol(const PlayerShip& playerShip, float deltaTime)
{
    sf::Angle destRotation = (position - patrolTarget).angle();
    rotation = Helper::lerpAngle(rotation, destRotation, ROTATION_LERP_WEIGHT * deltaTime);

    velocity = sf::Vector2f(0, -1).rotatedBy(rotation) * SPEED;

    engineActive = true;
}

void EnemyShip::randomisePatrolTarget()
{
    patrolTarget.x = rand() % static_cast<int>(WORLD_WIDTH);
    patrolTarget.y = rand() % static_cast<int>(WORLD_HEIGHT);
}

void EnemyShip::updateTargetItem(const PlayerShip& playerShip, float deltaTime)
{

}

void EnemyShip::updateTargetPlayer(const PlayerShip& playerShip, float deltaTime)
{

}

void EnemyShip::updateAttackPlayer(const PlayerShip& playerShip, float deltaTime)
{

}

void EnemyShip::updateFleePlayer(const PlayerShip& playerShip, float deltaTime)
{

}

void EnemyShip::avoidOtherShips(const std::vector<EnemyShip>& ships)
{

    // Move away from other closeby ships

    bool closeShipProximity = false;
    sf::Vector2f closeShipPos;
    for (const EnemyShip& ship : ships)
    {

        // Skip self
        if (id == ship.getID())
            continue;

        sf::Vector2f shipPos = ship.getPosition();
        float distanceSq = (position - shipPos).lengthSq();

        if(distanceSq <= SHIP_CLOSEST_RADIUS * SHIP_CLOSEST_RADIUS * SCALE)
        {

            // Not already found close ship
            if (!closeShipProximity)
            {
                closeShipPos = shipPos;
                closeShipProximity = true;
            }
            else
            {
                float closestDistanceSq = (position - closeShipPos).lengthSq();
                if (distanceSq < closestDistanceSq)
                {
                    closeShipPos = shipPos;
                }
            }

        }

    }


    if (closeShipProximity)
    {
        float velocityMagnitude = velocity.length();
        float distanceSq = (position - closeShipPos).lengthSq();
        float pushMult = 1 - (distanceSq / (SHIP_CLOSEST_RADIUS * SHIP_CLOSEST_RADIUS * SCALE));

        sf::Vector2f pushVector = (position - closeShipPos).normalized() * velocityMagnitude;

        velocity += pushMult * pushVector;
        velocity = velocity.normalized() * velocityMagnitude;
    }

}


bool EnemyShip::isBulletColliding(sf::Vector2f bulletPos)
{

    float distanceSq = (hitboxPosition - bulletPos).lengthSq();

    if (distanceSq < HITBOX_RADIUS * HITBOX_RADIUS * SCALE)
    {
        return true;
    }

    return false;

}


void EnemyShip::shoot()
{
    sf::Vector2f offset = sf::Vector2f(0, -6 * SCALE).rotatedBy(rotation);
    BulletManager::createEnemyBullet(position + offset, rotation);

    SoundManager::playSound(SoundType::EnemyShoot);
}


void EnemyShip::damage(int amount)
{

    if (!isAlive())
        return;

    flashTime = MAX_FLASH_TIME;

    health -= amount;

    if (isAlive())
        healthBar.updateValue(health);
    else
    {
        // Dead
        InventoryManager::addExperience(15);
        MissionManager::addToGoal(MissionType::Kill, 1);
        SoundManager::playSound(SoundType::ShipExplode);
    }
}


bool EnemyShip::isAlive()
{
    return (health > 0);
}

bool EnemyShip::isDestroyed()
{
    return (destroyedFrameIndex >= DESTROYED_ANIM_FRAMES - 1);
}

bool EnemyShip::canRemove()
{
    return (!isAlive() && isDestroyed());
}


EnemyShipData EnemyShip::generateData()
{

    EnemyShipData data;
    data.x = position.x;
    data.y = position.y;
    data.velx = velocity.x;
    data.vely = velocity.y;
    data.rot = rotation.asDegrees();
    data.hp = health;
    data.id = id;
    data.behaviourState = behaviourState;

    return data;

}


void EnemyShip::draw(sf::RenderWindow& window)
{

    if (isAlive())
    {
        drawAlive(window);
    }
    else
    {
        drawDestroyed(window);
    }

}


void EnemyShip::drawAlive(sf::RenderWindow& window)
{

    sf::Vector2f drawOffset = Camera::getDrawOffset();

    if (engineActive)
    {
        TextureDrawData engineDrawData = {
            TextureType::EnemyShipEngine,
            position + drawOffset,
            rotation,
            SCALE
        };

        sf::IntRect engineSubRect = sf::IntRect(sf::Vector2i(64 * engineFrameIndex, 0), sf::Vector2i(64, 64));

        TextureManager::drawSubTexture(window, engineDrawData, engineSubRect);
    }

    TextureDrawData drawData = {
        TextureType::EnemyShip,
        position + drawOffset,
        rotation,
        SCALE
    };

    TextureManager::drawTexture(window, drawData);

    if (flashTime > 0)
    {
        float flashAlpha = 210.0f * (flashTime / MAX_FLASH_TIME);

        drawData = {
            TextureType::EnemyShipFlash,
            position + drawOffset,
            rotation,
            SCALE,
            true,
            sf::Color(255, 255, 255, flashAlpha)
        };

        TextureManager::drawTexture(window, drawData);
    }

    healthBar.setDrawPosition(sf::Vector2f(position.x - 50, position.y - 50) + drawOffset);
    healthBar.draw(window);

}


void EnemyShip::drawDestroyed(sf::RenderWindow& window)
{

    sf::Vector2f drawOffset = Camera::getDrawOffset();

    TextureDrawData destroyedDrawData = {
        TextureType::EnemyShipDestroyed,
        position + drawOffset,
        rotation,
        SCALE
    };

    sf::IntRect destroyedSubRect = sf::IntRect(sf::Vector2i(64 * destroyedFrameIndex, 0), sf::Vector2i(64, 64));

    TextureManager::drawSubTexture(window, destroyedDrawData, destroyedSubRect);

}


sf::Vector2f EnemyShip::getPosition() const
{
    return position;
}


unsigned long long EnemyShip::getID() const
{
    return id;
}