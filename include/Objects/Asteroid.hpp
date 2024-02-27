// Asteroid.hpp

#ifndef ASTEROID_HPP
#define ASTEROID_HPP

// Include libraries
#include <SFML/Graphics.hpp>
#include <iostream>
#include <algorithm>
#include <json.hpp>

// Include headers
#include "Camera.hpp"
#include "Manager/TextureManager.hpp"
#include "Manager/ItemPickupManager.hpp"
#include "Manager/SoundManager.hpp"
#include "Manager/BulletManager.hpp"
#include "Objects/ItemPickupType.hpp"
#include "Objects/DrawableObject.hpp"
#include "Renderer/PlanetRenderer.hpp"
#include "PlanetAsteroidDrops.hpp"

// Structure containing all data related to an asteroid
// Used for saving
struct AsteroidData
{
    // Position of asteroid
    float x, y;
    // Rotation
    float rot;
    // Scale
    float scale;
    // "Depth" in game world, to create 3D illusion
    float depth;
    // Asteroid health remaining
    int hp;

    // Macro used to (de)serialise this struct when saving to and loading from JSON
    NLOHMANN_DEFINE_TYPE_INTRUSIVE(AsteroidData, x, y, rot, scale, depth, hp)
};

// Declare asteroid class
class Asteroid : public DrawableObject
{

// Public class functions
public:
    // Constructor, taking in a position for the asteroid
    Asteroid(sf::Vector2f position);

    // Update the asteroid
    void update(PlanetType currentPlanet, float deltaTime);

    // Draw the asteroid
    void draw(sf::RenderWindow& window) override;

    // Test whether the asteroid is colliding with a bullet at a given position
    bool isColliding(sf::Vector2f bulletTip);

    // Return whether the asteroid has any health remaining
    bool isAlive();

    // Get position, reverted back to standard depth level (is drawn at different "depth", so standard position will be incorrect)
    sf::Vector2f getNormalisedPosition();

    // Getter function for asteroid depth
    inline float getDepth() const {return depth;}

    // Create an asteroid data object which represents this asteroid
    AsteroidData generateData();

    // Override the data of this asteroid with an asteroid data object
    void setData(AsteroidData data);

// Private class functions
private:
    // Damage asteroid by amount
    void damage(int amount);

    // Draw asteroid in standard alive state
    void drawAsteroid(sf::RenderWindow& window);

    // Draw asteroid in explosion animation state
    void drawExplosion(sf::RenderWindow& window);

    // Spawn item pickups when asteroid is destroyed
    void spawnPickups(PlanetType currentPlanet);

// Private member variables
private:
    // Constant storing how long asteroid should flash white when damaged
    static constexpr float FLASH_TIME = 0.15f;

    // Constant storing maximum health of asteroid
    static constexpr int MAX_HEALTH = 50;

    // Constant storing how many frames there are to the asteroid cracking animation
    static constexpr int CRACK_FRAMES = 5;

    // Constant storing how many frames there are to the asteroid explosion animation
    static constexpr int EXPLOSION_FRAMES = 7;

    // Constant storing how long each frame of the asteroid explosion animation should last
    static constexpr float EXPLOSION_FRAME_MAX_TICK = 0.07f;

    // Variables storing position, rotation, and scale of asteroid
    sf::Vector2f position;
    sf::Angle rotation;
    float scale;

    // Variable storing "depth" of asteroid, which affects how it is drawn on the screen (gives "3D" effect)
    float depth;

    // Variable storing how long the asteroid has been flashing white for
    float flashTime;

    // Variable storing health remaining
    int health;

    // Variable storing whether the asteroid is current exploding or not
    bool exploding;

    // Variable storing the current frame of the explosion animation
    int explosionFrame;

    // Variable storing the time since the last frame change of the explosion animation
    float explosionFrameTick;

    // Variable storing whether the asteorid is alive
    bool alive;

};

#endif