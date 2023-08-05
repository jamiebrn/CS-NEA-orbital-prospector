//
// PlayerShip.hpp
// 
// All functions and data associated with player ship movement, position, rotation, etc.
//

#ifndef PLAYER_SHIP_HPP
#define PLAYER_SHIP_HPP

#include <cmath>
#include <array>

#include <SFML/Graphics.hpp>

#include "Constants.hpp"
#include "Manager/TextureManager.hpp"
#include "Objects/DrawableObject.hpp"
#include "Helper.hpp"
#include "Camera.hpp"
#include "Manager/BulletManager.hpp"
#include "Manager/ItemPickupManager.hpp"
#include "Manager/InventoryManager.hpp"
#include "Manager/SoundManager.hpp"

// PlayerShip class declaration
class PlayerShip : public DrawableObject
{

// Public functions
public:
    PlayerShip(sf::Vector2f position);

    void update(float deltaTime, sf::Vector2f mouse_position);

    void draw(sf::RenderWindow& window) override;

    void setPosition(sf::Vector2f new_position);
    sf::Vector2f getPosition();

// Private functions
private:
    void shootBullets();

// Private member variables
private:
    static constexpr float MAX_VELOCITY = 200;
    static constexpr float ACCELERATION = 11;
    static constexpr float DECELERATION = 16;

    static constexpr float SHOOT_COOLDOWN = 0.1;

    static constexpr float ITEM_PICKUP_RADIUS = 50;

    static constexpr std::array<sf::Vector2f, 2> bulletSpawnPos = {
        sf::Vector2f(-10.0f, -6.0f), sf::Vector2f(10.0f, -6.0f)
    };

    static constexpr float ROTATION_LERP_WEIGHT = 5;

    static constexpr float ENGINE_ANIM_TICK_MAX = 0.06;

    sf::Vector2f position, velocity;
    float direction;

    float shootCooldown;
    int currentGunIndex;

    int engineAnimationIndex;
    float engineAnimTick;
    bool engineActive;

};

#endif