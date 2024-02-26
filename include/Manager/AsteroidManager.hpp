// AsteroidManager.hpp

#ifndef ASTEROID_MANAGER_HPP
#define ASTEROID_MANAGER_HPP

// Include libraries
#include <vector>
#include <memory>
#include <SFML/Graphics.hpp>

// Include headers
#include "Objects/Asteroid.hpp"
#include "Camera.hpp"

// Declare asteroid manager class
class AsteroidManager
{

// Delete constructor as is a static class
private:
    AsteroidManager() = delete;

// Public class functions
public:
    // Create an asteroid
    static void createAsteroid(sf::Vector2f position);

    // Insert a previously-created asteroid into the manager
    static void insertAsteroid(std::unique_ptr<Asteroid> asteroid);

    // Update all asteroids
    static void updateAsteroids(PlanetType currentPlanet, float deltaTime);

    // Sort asteroids based on depth
    static void sortAsteroids();
    
    // Draw asteroids to screen
    static void drawAsteroids(sf::RenderWindow& window);

    // Reset manager (delete all asteroids)
    static void reset();

    // Get reference to asteroid vector if necessary
    static std::vector<std::unique_ptr<Asteroid>>& getAsteroids();

// Private member variables
private:
    // Vector of asteroids
    static std::vector<std::unique_ptr<Asteroid>> asteroids;

    // Constant referencing how often asteroids should be spawned
    static constexpr float SPAWN_COOLDOWN = 10;

    // Variable keeping track of when asteroids were last spawned
    static float lastSpawn;

};

#endif