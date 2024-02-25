#ifndef ASTEROID_MANAGER_HPP
#define ASTEROID_MANAGER_HPP

#include <vector>
#include <memory>

#include <SFML/Graphics.hpp>

#include "Objects/Asteroid.hpp"
#include "Camera.hpp"

class AsteroidManager
{

private:
    AsteroidManager() = delete;

public:
    static void createAsteroid(sf::Vector2f position);

    static void insertAsteroid(std::unique_ptr<Asteroid> asteroid);

    static void updateAsteroids(PlanetType currentPlanet, float deltaTime);

    static void sortAsteroids();
    
    static void drawAsteroids(sf::RenderWindow& window);

    static void reset();

    static std::vector<std::unique_ptr<Asteroid>>& getAsteroids();

private:
    static std::vector<std::unique_ptr<Asteroid>> asteroids;

    static constexpr float SPAWN_COOLDOWN = 10;

    static float lastSpawn;

};

#endif