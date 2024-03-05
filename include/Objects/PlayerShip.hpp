// PlayerShip.hpp

#ifndef PLAYER_SHIP_HPP
#define PLAYER_SHIP_HPP

// Include libraries
#include <SFML/Graphics.hpp>
#include <cmath>
#include <array>

// Include headers
#include "Constants.hpp"
#include "Manager/TextureManager.hpp"
#include "Objects/DrawableObject.hpp"
#include "Helper.hpp"
#include "Camera.hpp"
#include "Manager/BulletManager.hpp"
#include "Manager/ItemPickupManager.hpp"
#include "Manager/InventoryManager.hpp"
#include "Manager/UpgradeManager.hpp"
#include "Manager/MissionManager.hpp"
#include "Manager/SoundManager.hpp"

// PlayerShip class declaration
class PlayerShip : public DrawableObject
{

// Public class function
public:
    // Constructor taking in position as parameter
    PlayerShip(sf::Vector2f position);

    // Update player ship object position and rotation based on inputs
    void update(float deltaTime, sf::Vector2f mouse_position);

    // Draw player ship
    void draw(sf::RenderWindow& window) override;

    // Respawn
    void respawn();

    // Set player ship position
    void setPosition(sf::Vector2f new_position);

    // Get player ship position
    sf::Vector2f getPosition() const;

    // Get player ship health
    inline float getHealth() const {return health;}

    // Set player ship health
    inline void setHealth(float health) {this->health = health;}

    // Returns whether player ship is alive
    inline bool isAlive() const {return health > 0;}


// Private class functions
private:
    // Damage player ship by amount
    void damage(int amount);
    
    // Shoot bullets
    void shootBullets();


// Private member variables
private:
    // Constant values describing how player ship moves
    static constexpr float MAX_VELOCITY = 200;
    static constexpr float ACCELERATION = 11;
    static constexpr float DECELERATION = 16;

    // Constant value storing minimum time between player shooting
    static constexpr float SHOOT_COOLDOWN = 0.1;

    // Constant value storing radius at which the player can pick up items
    static constexpr float ITEM_PICKUP_RADIUS = 50;

    // Constant array storing relative positions to where bullets should be spawned when shooting
    static constexpr std::array<sf::Vector2f, 2> bulletSpawnPos = {
        sf::Vector2f(-10.0f, -6.0f), sf::Vector2f(10.0f, -6.0f)
    };

    // Constant value storing interpolation weight of player ship rotation
    static constexpr float ROTATION_LERP_WEIGHT = 5;

    // Constant value storing time between frame increment for engine animation
    static constexpr float ENGINE_ANIM_TICK_MAX = 0.06;

    // Constant value storing hitbox radius of player ship
    static constexpr float HITBOX_RADIUS = 80;

    // Constant value storing how long the player ship should flash white for when hit
    static constexpr float FLASH_TIME_MAX = 0.3f;

    // Variables storing position, velocity, and direction (rotation)
    sf::Vector2f position, velocity;
    float direction;

    // Variables storing player ship health data
    float health;

    // Variable storing time until player can respawn
    float respawnCount;

    // Variable storing time until player can next shoot
    float shootCooldown;

    // Variable storing which gun to shoot from next
    int currentGunIndex;

    // Variables storing data about engine animation playback
    int engineAnimationIndex;
    float engineAnimTick;

    // Variable keeping track of whether the engine is active
    bool engineActive;

    // Variable keeping track of how much longer the player ship should flash white for
    float flashTime;

};

#endif