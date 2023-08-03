#include "Manager/AsteroidManager.hpp"

std::vector<Asteroid> AsteroidManager::asteroids;

void AsteroidManager::createAsteroid(sf::Vector2f position)
{
    Asteroid asteroid(position);

    asteroids.push_back(asteroid);   
}

void AsteroidManager::updateAsteroids(float deltaTime)
{
    for (Asteroid& asteroid : asteroids)
    {
        asteroid.update(deltaTime);
    }

    for (auto asteroidIter = asteroids.begin(); asteroidIter != asteroids.end();)
    {
        if (!asteroidIter->isAlive())
        {
            asteroidIter = asteroids.erase(asteroidIter);
        }
        else
        {
            asteroidIter++;
        }
    }
}

void AsteroidManager::drawAsteroids(sf::RenderWindow& window)
{
    for (Asteroid& asteroid : asteroids)
    {
        asteroid.draw(window);
    }
}

std::vector<Asteroid>& AsteroidManager::getAsteroids()
{
    return asteroids;
}
