#ifndef ASTEROID_HPP
#define ASTEROID_HPP

#include <iostream>
#include <algorithm>
#include <json.hpp>

#include <SFML/Graphics.hpp>

#include "Camera.hpp"
#include "Manager/TextureManager.hpp"
#include "Manager/ItemPickupManager.hpp"
#include "Manager/SoundManager.hpp"
#include "Manager/BulletManager.hpp"
#include "Objects/ItemPickupType.hpp"
#include "Objects/DrawableObject.hpp"

struct AsteroidData
{
    float x, y;
    float rot;
    float scale;
    float depth;
    int hp;

    NLOHMANN_DEFINE_TYPE_INTRUSIVE(AsteroidData, x, y, rot, scale, depth, hp)
};

class Asteroid : public DrawableObject
{

public:
    Asteroid(sf::Vector2f position);

    void update(float deltaTime);

    void draw(sf::RenderWindow& window) override;

    bool isColliding(sf::Vector2f bulletTip);

    bool isAlive();
    sf::Vector2f getNormalisedPosition();
    inline float getDepth() const {return depth;}

    AsteroidData generateData();
    void setData(AsteroidData data);


private:
    void damage(int amount);

    void drawAsteroid(sf::RenderWindow& window);
    void drawExplosion(sf::RenderWindow& window);

    void spawnPickups();

private:
    static constexpr float FLASH_TIME = 0.15f;
    static constexpr int MAX_HEALTH = 50;

    static constexpr int CRACK_FRAMES = 5;
    static constexpr int EXPLOSION_FRAMES = 7;
    static constexpr float EXPLOSION_FRAME_MAX_TICK = 0.07f;

    sf::Vector2f position;
    sf::Angle rotation;
    float scale;
    float depth;

    float flashTime;
    int health;

    bool exploding;
    int explosionFrame;
    float explosionFrameTick;

    bool alive;

};

#endif