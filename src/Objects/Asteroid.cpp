#include "Objects/Asteroid.hpp"

Asteroid::Asteroid(sf::Vector2f position)
{
    this->position = position;
    rotation = sf::degrees(rand() % 360);
    scale = 4.5f + (rand() % 2);

    flashTime = 0;
    health = MAX_HEALTH;

    exploding = false;

    alive = true;
}

void Asteroid::update(float deltaTime)
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
            spawnPickups();
            alive = false;
        }
    }

}

void Asteroid::spawnPickups()
{
    int pickupCount = rand() % 3;
    for (int i = 0; i <= pickupCount; i++)
    {
        int radius = 18 * scale;
        float projection = rand() % radius;
        sf::Angle rotation = sf::degrees(rand() % 360);

        sf::Vector2f spawnPos = sf::Vector2f(0, -1).rotatedBy(rotation) * projection;
        spawnPos += position;

        ItemPickupType pickupType;
        int typeRand = rand() % 101;
        if (typeRand < 60)
        {
            pickupType = ItemPickupType::Rock;
        }
        else if (typeRand < 90)
        {
            pickupType = ItemPickupType::CopperChunk;
        }
        else
        {
            pickupType = ItemPickupType::IronChunk;
        }

        ItemPickupManager::addItem(pickupType, spawnPos);
    }
}

bool Asteroid::isColliding(sf::Vector2f bulletTip)
{

    if (exploding)
        return false;

    float distanceSq = (position - bulletTip).lengthSq();

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

    if (!Camera::isInView(position, sf::Vector2f(200, 200)))
        return;

    sf::Vector2f drawOffset = Camera::getDrawOffset();

    TextureDrawData drawData = {
        TextureType::AsteroidCrack,
        position + drawOffset,
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
            position + drawOffset,
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
        position + drawOffset,
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

AsteroidData Asteroid::generateData()
{

    AsteroidData data;
    data.x = position.x;
    data.y = position.y;
    data.rot = rotation.asDegrees();
    data.scale = scale;
    data.hp = health;

    return data;

}

void Asteroid::setData(AsteroidData data)
{
    position = sf::Vector2f(data.x, data.y);
    rotation = sf::degrees(data.rot);
    scale = data.scale;
    health = data.hp;
}