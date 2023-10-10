#ifndef ENEMY_SHIP_HPP
#define ENEMY_SHIP_HPP

#include <SFML/Graphics.hpp>
#include <json.hpp>
#include <chrono>
#include <vector>

#include "DrawableObject.hpp"
#include "Camera.hpp"
#include "Helper.hpp"
#include "Manager/TextureManager.hpp"
#include "Manager/InventoryManager.hpp"
#include "Manager/BulletManager.hpp"
#include "Manager/SoundManager.hpp"
#include "Objects/HealthBar.hpp"
#include "Objects/PlayerShip.hpp"

enum class EnemyShipBehaviour
{
    Idle,
    Attack,
};

struct EnemyShipData
{
    float x, y;
    float velx, vely;
    float rot;
    int hp;
    unsigned long long id;
    EnemyShipBehaviour behaviourState;

    NLOHMANN_DEFINE_TYPE_INTRUSIVE(
        EnemyShipData,
        x, y,
        velx, vely,
        rot,
        hp,
        id,
        behaviourState
    )
};

class EnemyShip : public DrawableObject
{

public:
    EnemyShip(sf::Vector2f position);

    EnemyShip(EnemyShipData data);

    void update(const PlayerShip& playerShip, const std::vector<EnemyShip>& ships, float deltaTime);

    void draw(sf::RenderWindow& window) override;

    bool isBulletColliding(sf::Vector2f bulletPos);

    bool isAlive();
    bool isDestroyed();
    bool canRemove();

    EnemyShipData generateData();

    sf::Vector2f getPosition() const;

    unsigned long long getID() const;

private:
    void updateIdle(const PlayerShip& playerShip, float deltaTime);
    void updateAttack(const PlayerShip& playerShip, const std::vector<EnemyShip>& ships, float deltaTime);

    void damage(int amount);

    void shoot();

    void drawAlive(sf::RenderWindow& window);
    void drawDestroyed(sf::RenderWindow& window);

private:
    static constexpr float SCALE = 6;

    static constexpr float SPEED = 100;
    static constexpr float ACCELERATION = 6;
    static constexpr float DECELERATION = 8;

    static constexpr int MAX_HEALTH = 20;

    static constexpr float SHOOT_COOLDOWN = 0.2;

    static constexpr float ROTATION_LERP_WEIGHT = 4;

    static constexpr float PLAYER_SPEED_RADIUS = 350;
    static constexpr float PLAYER_SHOOT_RADIUS = 300;
    static constexpr float SHIP_CLOSEST_RADIUS = 8 * SCALE;

    static constexpr float HITBOX_RADIUS = 5 * SCALE;

    static constexpr int ENGINE_ANIM_FRAMES = 10;
    static constexpr float ENGINE_ANIM_TICK_MAX = 0.06;

    static constexpr int DESTROYED_ANIM_FRAMES = 10;
    static constexpr float DESTROYED_ANIM_TICK_MAX = 0.06;

    static constexpr float MAX_FLASH_TIME = 0.2;

    unsigned long long id;

    sf::Vector2f position, velocity;
    sf::Angle rotation;
    sf::Angle destRotation;

    EnemyShipBehaviour behaviourState;

    int health;
    HealthBar healthBar;

    float shootCooldown;

    sf::Vector2f hitboxPosition;

    bool engineActive;
    float engineFrameTick;
    int engineFrameIndex;

    float destroyedFrameTick;
    int destroyedFrameIndex;

    float flashTime;

};

#endif