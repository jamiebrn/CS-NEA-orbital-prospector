#include "Objects/EnemyShip.hpp"

EnemyShip::EnemyShip(sf::Vector2f position)
    : healthBar(sf::Vector2f(0, 0), sf::Vector2f(100, 30), MAX_HEALTH)
{

    this->position = position;

    velocity = sf::Vector2f(0, 0);
    rotation = sf::degrees(0);

    id = std::chrono::system_clock::now().time_since_epoch() / std::chrono::milliseconds(1);

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

    engineActive = false;

    flashTime = 0;

    healthBar.updateValue(health);

}

void EnemyShip::update(sf::Vector2f playerPos, const std::vector<EnemyShip>& ships, float deltaTime)
{

    // Rotation

    if (velocity.lengthSq() > 0)
    {
        sf::Angle destRot = velocity.angle() + sf::degrees(90);
        rotation = Helper::lerpAngle(rotation, destRot, ROTATION_LERP_WEIGHT * deltaTime);
    }


    // Move towards player

    float distanceSq = (position - playerPos).lengthSq();
    if (distanceSq >= PLAYER_SHOOT_RADIUS * PLAYER_SHOOT_RADIUS)
    {
        sf::Vector2f directionVector = (playerPos - position).normalized();

        velocity.x = Helper::lerp(velocity.x, directionVector.x * SPEED, ACCELERATION * deltaTime);
        velocity.y = Helper::lerp(velocity.y, directionVector.y * SPEED, ACCELERATION * deltaTime);
    
        engineActive = true;
    }
    else
    {
        velocity.x = Helper::lerp(velocity.x, 0, DECELERATION * deltaTime);
        velocity.y = Helper::lerp(velocity.y, 0, DECELERATION * deltaTime);

        engineActive = false;
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
        velocity = (position - closeShipPos).normalized() * velocityMagnitude;
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
        damage(1);

        return true;
    }

    return false;

}

void EnemyShip::damage(int amount)
{
    flashTime = MAX_FLASH_TIME;

    health -= amount;

    if (health >= 0)
        healthBar.updateValue(health);
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

    // Debug

    sf::CircleShape closeBox(SHIP_CLOSEST_RADIUS);
    closeBox.setPosition(position + drawOffset);
    closeBox.setOrigin(sf::Vector2f(SHIP_CLOSEST_RADIUS, SHIP_CLOSEST_RADIUS));
    closeBox.setFillColor(sf::Color(100, 30, 30, 100));
    window.draw(closeBox);

    sf::Vertex line[] = {sf::Vertex(position + drawOffset), sf::Vertex(position + velocity * 10.0f + drawOffset)};
    window.draw(line, 2, sf::Lines);

}

sf::Vector2f EnemyShip::getPosition() const
{
    return position;
}

unsigned long long EnemyShip::getID() const
{
    return id;
}