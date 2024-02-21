#include "Manager/AsteroidManager.hpp"

std::vector<std::unique_ptr<Asteroid>> AsteroidManager::asteroids;
float AsteroidManager::lastSpawn = 0;

void AsteroidManager::createAsteroid(sf::Vector2f position)
{
    std::unique_ptr<Asteroid> asteroid = std::make_unique<Asteroid>(position);

    asteroids.push_back(std::move(asteroid));
}

void AsteroidManager::insertAsteroid(std::unique_ptr<Asteroid> asteroid)
{
    asteroids.push_back(std::move(asteroid));
}

void AsteroidManager::updateAsteroids(PlanetType currentPlanet, float deltaTime)
{

    lastSpawn += deltaTime;

    if (lastSpawn >= SPAWN_COOLDOWN)
    {
        lastSpawn = 0;

        int toSpawn = ASTEROID_MAX - asteroids.size();
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

    for (std::unique_ptr<Asteroid>& asteroid : asteroids)
    {
        asteroid->update(currentPlanet, deltaTime);
    }

    for (auto asteroidIter = asteroids.begin(); asteroidIter != asteroids.end();)
    {
        if (!asteroidIter->get()->isAlive())
        {
            asteroidIter = asteroids.erase(asteroidIter);
        }
        else
        {
            asteroidIter++;
        }
    }

    std::sort(asteroids.begin(), asteroids.end(),
        [](std::unique_ptr<Asteroid> const& asteroid, std::unique_ptr<Asteroid> const& asteroid2)
        {
            return asteroid->getDepth() > asteroid2->getDepth();
        }
    );


}

void AsteroidManager::drawAsteroids(sf::RenderWindow& window)
{
    for (std::unique_ptr<Asteroid>& asteroid : asteroids)
    {
        asteroid->draw(window);
    }
}

void AsteroidManager::reset()
{
    asteroids.clear();
}

std::vector<std::unique_ptr<Asteroid>>& AsteroidManager::getAsteroids()
{
    return asteroids;
}
