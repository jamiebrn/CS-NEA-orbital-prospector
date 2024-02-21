#include "Objects/Asteroid.hpp"

Asteroid::Asteroid(sf::Vector2f position)
{
    this->position = position;
    rotation = sf::degrees(rand() % 360);
    scale = 4.5f + (rand() % 2);
    depth = 1.0f + (static_cast<float>(rand() % 700) / 500.0f) - 0.2f;

    flashTime = 0;
    health = MAX_HEALTH;

    exploding = false;

    alive = true;
}

void Asteroid::update(PlanetType currentPlanet, float deltaTime)
{

    if (!exploding)
    {
        flashTime = std::max(flashTime - deltaTime, 0.0f);

        // Check bullet collision
        for (Bullet& bullet : BulletManager::getBullets())
        {
            sf::Vector2f bulletPos = bullet.getPosition();
            if (isColliding(bulletPos))
            {
                damage(1);
                bullet.kill();
            }
        }

        for (Bullet& bullet : BulletManager::getEnemyBullets())
        {
            sf::Vector2f bulletPos = bullet.getPosition();
            if (isColliding(bulletPos))
            {
                damage(1);
                bullet.kill();
            }
        }
        
        return;
    }

    // When exploding

    explosionFrameTick += deltaTime;
    if (explosionFrameTick >= EXPLOSION_FRAME_MAX_TICK)
    {
        explosionFrameTick = 0;
        explosionFrame++;
        if (explosionFrame >= EXPLOSION_FRAMES)
        {
            spawnPickups(currentPlanet);
            alive = false;
        }
    }

}

void Asteroid::spawnPickups(PlanetType currentPlanet)
{
    int pickupCount = rand() % 3;
    for (int i = 0; i <= pickupCount; i++)
    {
        
        int radius = (18 * scale) / depth;
        float projection = rand() % radius;
        sf::Angle rotation = sf::degrees(rand() % 360);

        sf::Vector2f spawnPos = sf::Vector2f(0, -1).rotatedBy(rotation) * projection;
        spawnPos += getNormalisedPosition();

        ItemPickupType pickupType;
        float typeRand = (rand() % 101) / 100;

        float cumulativeChance = 0.0f;
        for (std::pair<ItemPickupType, float> pickupChance : asteroidDropRates.at(currentPlanet))
        {
            cumulativeChance += pickupChance.second;
            if (typeRand <= cumulativeChance)
            {
                ItemPickupManager::addItem(pickupChance.first, spawnPos);
                break;
            }
        }

    }
}

bool Asteroid::isColliding(sf::Vector2f bulletTip)
{

    if (exploding)
        return false;

    float distanceSq = (getNormalisedPosition() - bulletTip).lengthSq();

    float radius = 18 * scale;

    if (distanceSq < radius * radius)
    {
        return true;
    }

    return false;

}

void Asteroid::damage(int amount)
{

    flashTime = FLASH_TIME;
    health -= amount;

    if (health <= 0)
    {
        exploding = true;
        explosionFrame = 0;
        explosionFrameTick = 0;

        SoundManager::playSound(SoundType::AsteroidExplode);
    }

}

void Asteroid::draw(sf::RenderWindow& window)
{

    if (!exploding)
    {
        drawAsteroid(window);
    }
    else
    {
        drawExplosion(window);
    }

}

void Asteroid::drawAsteroid(sf::RenderWindow& window)
{


    if (!Camera::isInView(getNormalisedPosition(), sf::Vector2f(200, 200)))
        return;

    sf::Vector2f drawOffset = Camera::getDrawOffset();
    
    TextureDrawData drawData = {
        TextureType::AsteroidCrack,
        position + drawOffset / depth,
        rotation,
        scale
    };

    int subCrackFrames = static_cast<int>((float)(CRACK_FRAMES - 1) * ((float)health / (float)MAX_HEALTH));
    int crackFrame = CRACK_FRAMES - subCrackFrames - 1;

    sf::IntRect subRect(sf::Vector2i(crackFrame * 96, 0), sf::Vector2i(96, 96));

    TextureManager::drawSubTexture(window, drawData, subRect);

    if (flashTime > 0)
    {
        float flashAlpha = 210.0f * (flashTime / FLASH_TIME);

        drawData = {
            TextureType::AsteroidFlash,
            position + drawOffset / depth,
            rotation,
            scale,
            true,
            sf::Color(255, 255, 255, flashAlpha)
        };

        TextureManager::drawTexture(window, drawData);
    }

}

void Asteroid::drawExplosion(sf::RenderWindow& window)
{

    sf::Vector2f drawOffset = Camera::getDrawOffset();

    TextureDrawData drawData = {
        TextureType::AsteroidExplode,
        position + drawOffset / depth,
        rotation,
        scale
    };

    sf::IntRect subRect(sf::Vector2i(explosionFrame * 96, 0), sf::Vector2i(96, 96));

    TextureManager::drawSubTexture(window, drawData, subRect);

}

bool Asteroid::isAlive()
{
    return alive;
}

sf::Vector2f Asteroid::getNormalisedPosition()
{

    sf::Vector2f drawOffset = Camera::getDrawOffset();

    sf::Vector2f normalisedPosition = position + drawOffset * Helper::unprojectDepthMultipier(depth, 1);

    return normalisedPosition;

}

AsteroidData Asteroid::generateData()
{

    AsteroidData data;
    data.x = position.x;
    data.y = position.y;
    data.rot = rotation.asDegrees();
    data.scale = scale;
    data.depth = depth;
    data.hp = health;

    return data;

}

void Asteroid::setData(AsteroidData data)
{
    position = sf::Vector2f(data.x, data.y);
    rotation = sf::degrees(data.rot);
    scale = data.scale;
    depth = data.depth;
    health = data.hp;
}