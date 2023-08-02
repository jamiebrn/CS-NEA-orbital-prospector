#ifndef ASTEROID_MANAGER_HPP
#define ASTEROID_MANAGER_HPP

#include <vector>

#include <SFML/Graphics.hpp>

#include "Asteroid.hpp"

class AsteroidManager
{

private:
    AsteroidManager() = delete;

public:
    static void createAsteroid(sf::Vector2f position);

    static void updateAsteroids(float deltaTime);

    static void drawAsteroids(sf::RenderWindow& window);

private:
    static std::vector<Asteroid> asteroids;

};

#endif