// EnemyShip.hpp

#ifndef ENEMY_SHIP_HPP
#define ENEMY_SHIP_HPP

// Include libraries
#include <SFML/Graphics.hpp>
#include <json.hpp>
#include <chrono>
#include <vector>

// Include headers
#include "DrawableObject.hpp"
#include "Constants.hpp"
#include "Camera.hpp"
#include "Helper.hpp"
#include "Manager/TextureManager.hpp"
#include "Manager/InventoryManager.hpp"
#include "Manager/UpgradeManager.hpp"
#include "Manager/ItemPickupManager.hpp"
#include "Manager/BulletManager.hpp"
#include "Manager/SoundManager.hpp"
#include "Manager/MissionManager.hpp"
#include "Objects/HealthBar.hpp"
#include "Objects/PlayerShip.hpp"

// Enum representing all possible states of the enemy ship AI
enum class EnemyShipBehaviourState
{
    Patrol,
    TargetItem,
    TargetPlayer,
    AttackPlayer,
    FleePlayer
};

// Struct storing all data necessary to save an enemy ship
struct EnemyShipData
{
    // Position
    float x, y;
    // Velocity
    float velx, vely;
    // Rotation
    float rot;
    // Health remaining
    int hp;
    // ID
    uint64_t id;
    // Current state
    EnemyShipBehaviourState behaviourState;

    // Macro used for (de)serialising struct
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

// Declare enemy ship class
class EnemyShip : public DrawableObject
{

// Public class functions
public:
    // Constructor taking in a position
    EnemyShip(sf::Vector2f position);

    // Constructor taking in an enemy ship data object
    EnemyShip(EnemyShipData data);

    // Update enemy ship
    void update(const PlayerShip& playerShip, const std::vector<EnemyShip>& ships, float deltaTime);

    // Draw enemy ship
    void draw(sf::RenderWindow& window) override;

    // Test collision with player ship bullets
    bool isBulletColliding(sf::Vector2f bulletPos);

    // Returns whether any health is remaining
    bool isAlive();
    // Returns whether destroyed animation is finished
    bool isDestroyed();
    // Returns whether the enemy ship can be freed from memory
    bool canRemove();

    // Create enemy ship data object from enemy ship
    EnemyShipData generateData();

    // Get position of enemy ship
    sf::Vector2f getPosition() const;

    // Get ID of enemy ship
    uint64_t getID() const;

// Private class functions
private:
    // Update in patrol state
    void updatePatrol(const PlayerShip& playerShip, float deltaTime);
    // Update in target item state
    void updateTargetItem(const PlayerShip& playerShip, float deltaTime);
    // Update in target player state
    void updateTargetPlayer(const PlayerShip& playerShip, float deltaTime);
    // Update in attack player state
    void updateAttackPlayer(const PlayerShip& playerShip, float deltaTime);
    // Update in flee player state
    void updateFleePlayer(const PlayerShip& playerShip, float deltaTime);

    // Test collision with and avoid other enemy ships
    void avoidOtherShips(const std::vector<EnemyShip>& ships);

    // Randomise the enemy ship patrol target
    void randomisePatrolTarget();

    // Damage enemy ship by amount
    void damage(float amount, const PlayerShip& playerShip);

    // Shoot bullet
    void shoot();

    // Draw enemy ship in alive state
    void drawAlive(sf::RenderWindow& window);
    // Draw enemy ship in destroyed state
    void drawDestroyed(sf::RenderWindow& window);

// Private member variables
private:
    // Constant storing scale of enemy ship sprite
    static constexpr float SCALE = 6;

    // Constant storing enemy ship base speed
    static constexpr float SPEED = 100;

    // Constant storing enemy ship max health
    static constexpr int MAX_HEALTH = 20;

    // Constant storing enemy ship shoot cooldown
    static constexpr float SHOOT_COOLDOWN = 0.2;

    // Constant storing the interpolation weight of the enemy ship's rotation
    static constexpr float ROTATION_LERP_WEIGHT = 4;

    // Constatnt storing the range in which enemy ships can get within each other
    static constexpr float SHIP_CLOSEST_RADIUS = 8 * SCALE;

    // Constant storing the size of the enemy ship hitbox
    static constexpr float HITBOX_RADIUS = 5 * SCALE;

    // Constants storing data related to the engine animation
    static constexpr int ENGINE_ANIM_FRAMES = 10;
    static constexpr float ENGINE_ANIM_TICK_MAX = 0.06;

    // Constants storing data related to the destroyed ship animation
    static constexpr int DESTROYED_ANIM_FRAMES = 10;
    static constexpr float DESTROYED_ANIM_TICK_MAX = 0.06;

    // Constant storing how long the enemy ship flashes for when damaged
    static constexpr float MAX_FLASH_TIME = 0.2;

    // Variable storing enemy ship ID (ID is ms since Jan 1 1970)
    uint64_t id;

    // Variables storing position, velocity, and rotation
    sf::Vector2f position, velocity;
    sf::Angle rotation;
    sf::Angle destRotation;

    // Variable storing state of enemy ship
    EnemyShipBehaviourState behaviourState;

    // Variable storing the position of the target where enemy ship is headed
    sf::Vector2f patrolTarget;

    // Variable storing health remaining
    float health;

    // Variable storing health bar object
    HealthBar healthBar;

    // Variable storing the time since the enemy ship last shot a bullet
    float shootCooldown;

    // Variable storing the position of the enemy ship hitbox
    sf::Vector2f hitboxPosition;

    // Variable storing whether the enemy ship engine is active
    bool engineActive;

    // Variables storing the engine animation data
    float engineFrameTick;
    int engineFrameIndex;

    // Variables storing the destroyed ship animation data
    float destroyedFrameTick;
    int destroyedFrameIndex;

    // Variable storing time enemy ship has been flashing white for
    float flashTime;

};

#endif