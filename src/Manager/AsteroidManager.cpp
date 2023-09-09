#include "Manager/AsteroidManager.hpp"

std::vector<Asteroid> AsteroidManager::asteroids;
float AsteroidManager::lastSpawn = 0;

void AsteroidManager::createAsteroid(sf::Vector2f position)
{
    Asteroid asteroid(position);

    asteroids.push_back(asteroid);   
}

void AsteroidManager::insertAsteroid(Asteroid asteroid)
{
    asteroids.push_back(asteroid);   
}

void AsteroidManager::updateAsteroids(float deltaTime)
{

    lastSpawn += deltaTime;

    if (lastSpawn >= SPAWN_COOLDOWN)
    {
        lastSpawn = 0;

        int toSpawn = SPAWN_MAX - asteroids.size();
        for (int i = 0; i < toSpawn; i++)
        {
            sf::Vector2f position(rand() % static_cast<int>(WORLD_WIDTH), rand() % static_cast<int>(WORLD_HEIGHT));
            
            sf::Vector2f cameraPos = -Camera::getDrawOffset();
            float minX = cameraPos.x - 200;
            float minY = cameraPos.y - 200;
            float maxX = cameraPos.x + WINDOW_WIDTH + 200;
            float maxY = cameraPos.y + WINDOW_HEIGHT + 200;

            if (position.x > minX && position.y > minY && position.x < maxX && position.y < maxY)
                continue;
            
            AsteroidManager::createAsteroid(position);
        }
    }

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

void AsteroidManager::empty()
{
    asteroids.clear();
}

std::vector<Asteroid>& AsteroidManager::getAsteroids()
{
    return asteroids;
}
