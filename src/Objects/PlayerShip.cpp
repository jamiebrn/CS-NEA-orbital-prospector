#include "Objects/PlayerShip.hpp"

// Initialise player ship object
PlayerShip::PlayerShip(sf::Vector2f position)
{

    this->position = position;
    velocity = sf::Vector2f(0, 0);
    direction = 0;

    maxHealth = STARTING_MAX_HEALTH;
    health = maxHealth;

    shootCooldown = 0;
    currentGunIndex = 0;

    engineAnimationIndex = 0;
    engineAnimTick = 0;
    engineActive = false;

    flashTime = 0;

}

// Update player ship object position and rotation based on inputs
void PlayerShip::update(float deltaTime, sf::Vector2f mouse_position)
{

    // Movement

    sf::Vector2f drawOffset = Camera::getDrawOffset();

    float toMouseAngle = std::atan2(mouse_position.y - position.y - drawOffset.y, mouse_position.x - position.x - drawOffset.x);
    sf::Angle destination_direction = sf::radians(toMouseAngle + PI / 2);
    sf::Angle current_direction = Helper::lerpAngle(sf::radians(direction), destination_direction, ROTATION_LERP_WEIGHT * deltaTime);
    direction = current_direction.asRadians();

    if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
    {
        sf::Vector2f directionVector = sf::Vector2f(0, -1);
        directionVector = directionVector.rotatedBy(sf::radians(direction));

        velocity.x = Helper::lerp(velocity.x, directionVector.x * MAX_VELOCITY, ACCELERATION * deltaTime);
        velocity.y = Helper::lerp(velocity.y, directionVector.y * MAX_VELOCITY, ACCELERATION * deltaTime);

        engineActive = true;
    }
    else
    {
        velocity.x = Helper::lerp(velocity.x, 0, DECELERATION * deltaTime);
        velocity.y = Helper::lerp(velocity.y, 0, DECELERATION * deltaTime);

        engineActive = false;
    }

    if (isAlive())
    {

        position += velocity * deltaTime;

        // Enemy bullet collision

        for (Bullet& bullet : BulletManager::getEnemyBullets())
        {
            float lengthSq = (position - bullet.getPosition()).lengthSq();
            if (lengthSq <= HITBOX_RADIUS * HITBOX_RADIUS)
            {
                damage(1);
                bullet.kill();
            }
        }

        // Shooting

        shootCooldown += deltaTime;

        if (sf::Mouse::isButtonPressed(sf::Mouse::Right) && shootCooldown >= SHOOT_COOLDOWN)
        {
            shootCooldown = 0;
            shootBullets();

            currentGunIndex = (currentGunIndex + 1) % bulletSpawnPos.size();
        }

        // Item pickups

        std::vector<ItemPickupType> pickedUp = ItemPickupManager::testCollectedPickups(position, ITEM_PICKUP_RADIUS);
        for (ItemPickupType item : pickedUp)
        {
            InventoryManager::addItem(item, 1);
            InventoryManager::addExperience(InventoryManager::itemPrice(item));
        }
        if (pickedUp.size() > 0)
        {
            SoundManager::playSound(SoundType::ItemPickup);
        }

    }
    else
    {
        // When dead

        respawnCount -= deltaTime;
        if (respawnCount <= 0)
        {
            respawn();
        }
    }

    // Animation

    if (engineActive)
    {
        engineAnimTick += deltaTime;
        if (engineAnimTick >= ENGINE_ANIM_TICK_MAX)
        {
            engineAnimTick = 0;
            engineAnimationIndex = (engineAnimationIndex + 1) % 10;
        }
    }

    flashTime -= deltaTime;


}

void PlayerShip::respawn()
{

    position = sf::Vector2f(5000, 5000);
    health = maxHealth;

}

void PlayerShip::damage(int amount)
{

    if (!isAlive())
        return;

    health -= amount;

    flashTime = FLASH_TIME_MAX;

    if (!isAlive())
    {
        respawnCount = 5;
    }

}

void PlayerShip::shootBullets()
{

    sf::Vector2f localSpawnPos = bulletSpawnPos[currentGunIndex];

    sf::Vector2f globalPosition = position;
    globalPosition += localSpawnPos.rotatedBy(sf::radians(direction)) * 4.0f;

    BulletManager::createBullet(globalPosition, sf::radians(direction));

    SoundManager::playSound(SoundType::Shoot);

}

// Draw player ship object at position and rotation through texture manager
void PlayerShip::draw(sf::RenderWindow& window)
{

    if (!isAlive())
        return;

    sf::Vector2f drawOffset = Camera::getDrawOffset();


    // Draw engine trail

    if (engineActive)
    {
        TextureDrawData engineDrawData = {
            TextureType::PlayerShipEngine,
            position + drawOffset,
            sf::radians(direction),
            4
        };

        sf::IntRect engineSubRect = sf::IntRect(sf::Vector2i(64 * engineAnimationIndex, 0), sf::Vector2i(64, 64));

        TextureManager::drawSubTexture(window, engineDrawData, engineSubRect);
    }


    // Draw ship

    TextureDrawData shipDrawData = {
        TextureType::PlayerShip,
        position + drawOffset,
        sf::radians(direction),
        4
    };

    TextureManager::drawTexture(window, shipDrawData);


    // Draw flash effect from being damaged

    if (flashTime > 0)
    {
        float flashAlpha = (flashTime / FLASH_TIME_MAX) * 210;

        TextureDrawData flashDrawData = {
            TextureType::PlayerShipFlash,
            position + drawOffset,
            sf::radians(direction),
            4,
            true,
            sf::Color(255, 255, 255, flashAlpha)
        };

        TextureManager::drawTexture(window, flashDrawData);
    }

}

// Set player ship position
void PlayerShip::setPosition(sf::Vector2f new_position)
{
    position = new_position;
}

// Get player ship position
sf::Vector2f PlayerShip::getPosition()
{
    return position;
}