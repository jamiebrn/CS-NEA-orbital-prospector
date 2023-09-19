#ifndef ENEMY_SHIP_HPP
#define ENEMY_SHIP_HPP

#include <SFML/Graphics.hpp>
#include <json.hpp>

#include "DrawableObject.hpp"
#include "Camera.hpp"
#include "Helper.hpp"
#include "Manager/TextureManager.hpp"
#include "Objects/HealthBar.hpp"

struct EnemyShipData
{
    float x, y;
    float velx, vely;
    float rot;
    int hp;

    NLOHMANN_DEFINE_TYPE_INTRUSIVE(
        EnemyShipData,
        x, y,
        velx, vely,
        rot,
        hp
    )
};

class EnemyShip : public DrawableObject
{

public:
    EnemyShip(sf::Vector2f position);

    EnemyShip(EnemyShipData data);

    void update(sf::Vector2f playerPos, float deltaTime);

    void draw(sf::RenderWindow& window) override;

    bool isBulletColliding(sf::Vector2f bulletPos);

    bool isAlive();

    EnemyShipData generateData();

    sf::Vector2f getPosition() const;

private:
    void damage(int amount);

private:
    static constexpr float SCALE = 6;

    static constexpr float SPEED = 100;
    static constexpr float ACCELERATION = 6;
    static constexpr float DECELERATION = 8;

    static constexpr int MAX_HEALTH = 20;

    static constexpr float ROTATION_LERP_WEIGHT = 4;

    static constexpr float PLAYER_SHOOT_RADIUS = 350;

    static constexpr float HITBOX_RADIUS = 5 * SCALE;

    static constexpr int ENGINE_ANIM_FRAMES = 10;
    static constexpr float ENGINE_ANIM_TICK_MAX = 0.06;

    static constexpr float MAX_FLASH_TIME = 0.2;

    sf::Vector2f position, velocity;
    sf::Angle rotation;

    int health;
    HealthBar healthBar;

    sf::Vector2f hitboxPosition;

    bool engineActive;
    float engineFrameTick;
    int engineFrameIndex;

    float flashTime;

};

#endif