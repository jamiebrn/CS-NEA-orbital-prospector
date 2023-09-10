#ifndef ASTEROID_MANAGER_HPP
#define ASTEROID_MANAGER_HPP

#include <vector>

#include <SFML/Graphics.hpp>

#include "Objects/Asteroid.hpp"
#include "Camera.hpp"

class AsteroidManager
{

private:
    AsteroidManager() = delete;

public:
    static void createAsteroid(sf::Vector2f position);

    static void insertAsteroid(Asteroid asteroid);

    static void updateAsteroids(float deltaTime);

    static void drawAsteroids(sf::RenderWindow& window);

    static void reset();

    static std::vector<Asteroid>& getAsteroids();

private:
    static std::vector<Asteroid> asteroids;

    static constexpr float SPAWN_COOLDOWN = 10;

    static float lastSpawn;

};

#endif