#include "Objects/EnemyShip.hpp"

EnemyShip::EnemyShip(sf::Vector2f position)
    : healthBar(sf::Vector2f(0, 0), sf::Vector2f(100, 30), MAX_HEALTH)
{

    this->position = position;

    velocity = sf::Vector2f(0, 0);
    rotation = sf::degrees(0);

    id = std::chrono::system_clock::now().time_since_epoch() / std::chrono::milliseconds(1);

    shootCooldown = 0;

    hitboxPosition = sf::Vector2f(0, 0);

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

    id = data.id;

    shootCooldown = 0;

    engineActive = false;

    flashTime = 0;

    healthBar.updateValue(health);

}

void EnemyShip::update(sf::Vector2f playerPos, const std::vector<EnemyShip>& ships, float deltaTime)
{

    // Rotation

    if (velocity.lengthSq() > 0)
        destRotation = (position - playerPos).angle() - sf::degrees(90);

    // Move towards player

    float distanceSq = (position - playerPos).lengthSq();

    float inverseDist = (distanceSq / (PLAYER_SPEED_RADIUS * PLAYER_SPEED_RADIUS * SCALE));
    float currentSpeed = SPEED * std::max(1.0f, (1 - inverseDist) * 7);

    float rotationLerp = ROTATION_LERP_WEIGHT * std::clamp((inverseDist) * 3.5f, 0.3f, 1.0f);
    rotation = Helper::lerpAngle(rotation, destRotation, rotationLerp * deltaTime);

    sf::Vector2f directionVector = sf::Vector2f(0, -1).rotatedBy(rotation);

    velocity.x = Helper::lerp(velocity.x, directionVector.x * currentSpeed, ACCELERATION * deltaTime);
    velocity.y = Helper::lerp(velocity.y, directionVector.y * currentSpeed, ACCELERATION * deltaTime);

    engineActive = true;

    // Shoot player

    shootCooldown += deltaTime;

    if (distanceSq <= PLAYER_SHOOT_RADIUS * PLAYER_SHOOT_RADIUS * SCALE && shootCooldown >= SHOOT_COOLDOWN)
    {
        shootCooldown = 0;
        shoot();
    }


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

    
    // Update variables

    position += velocity * deltaTime;

    sf::Vector2f hitboxOffset = -sf::Vector2f(0, -1).rotatedBy(rotation) * 2.0f * SCALE;
    hitboxPosition = position + hitboxOffset;

    flashTime = std::max(flashTime - deltaTime, 0.0f);

    healthBar.update(deltaTime);

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
    BulletManager::createEnemyBullet(position, rotation);
}

void EnemyShip::damage(int amount)
{

    if (health <= 0)
        return;

    flashTime = MAX_FLASH_TIME;

    health -= amount;

    if (health > 0)
        healthBar.updateValue(health);
    else
    {
        // Dead
        InventoryManager::addExperience(15);
    }
}

bool EnemyShip::isAlive()
{
    return (health > 0);
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

    return data;

}

void EnemyShip::draw(sf::RenderWindow& window)
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

    healthBar.setDrawPosition(sf::Vector2f(position.x - 50, position.y - 50) + drawOffset);
    healthBar.draw(window);

}

sf::Vector2f EnemyShip::getPosition() const
{
    return position;
}

unsigned long long EnemyShip::getID() const
{
    return id;
}