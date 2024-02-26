// AsteroidManager.cpp

#include "Manager/AsteroidManager.hpp"

// Initialise member variables (must be done as static class, so has no constructor)
std::vector<std::unique_ptr<Asteroid>> AsteroidManager::asteroids;
float AsteroidManager::lastSpawn = 0;

// Create asteroid
void AsteroidManager::createAsteroid(sf::Vector2f position)
{
    // Create pointer to asteroid object at certain world position
    std::unique_ptr<Asteroid> asteroid = std::make_unique<Asteroid>(position);

    // Move asteroid pointer into asteroids vector
    asteroids.push_back(std::move(asteroid));
}

// Insert asteroid
void AsteroidManager::insertAsteroid(std::unique_ptr<Asteroid> asteroid)
{
    // Move asteroid pointer into asteroids vector
    asteroids.push_back(std::move(asteroid));
}

// Update all asteroids
void AsteroidManager::updateAsteroids(PlanetType currentPlanet, float deltaTime)
{

    // Add to last spawn, to keep track of when an asteroid was last spawned
    lastSpawn += deltaTime;

    // If last spawn timer has reached spawn cooldown time, spawn asteroids
    if (lastSpawn >= SPAWN_COOLDOWN)
    {
        // Reset last spawn variable
        lastSpawn = 0;

        // Calculate amount of asteroids needed to spawn to reach max asteroids
        int toSpawn = ASTEROID_MAX - asteroids.size();

        // Spawn amount of asteroids calculated
        for (int i = 0; i < toSpawn; i++)
        {
            // Randomise world position of asteroid
            sf::Vector2f position(rand() % static_cast<int>(WORLD_WIDTH), rand() % static_cast<int>(WORLD_HEIGHT));
            
            // Get screen bounds, to prevent asteroid spawning on screen
            sf::Vector2f cameraPos = -Camera::getDrawOffset();
            float minX = cameraPos.x - 200;
            float minY = cameraPos.y - 200;
            float maxX = cameraPos.x + WINDOW_WIDTH + 200;
            float maxY = cameraPos.y + WINDOW_HEIGHT + 200;

            // If asteroid position is within screen bounds, don't spawn this asteroid
            if (position.x > minX && position.y > minY && position.x < maxX && position.y < maxY)
                continue;
            
            // Create asteroid with generated position
            createAsteroid(position);

            // Resort asteroid vector, as new data has been added
            sortAsteroids();
        }
    }

    // Iterate over every asteroid and update
    for (std::unique_ptr<Asteroid>& asteroid : asteroids)
    {
        // Update asteroid with the current planet (needed to choose what items to drop if destroyed) and delta time
        asteroid->update(currentPlanet, deltaTime);
    }

    // Iterate over every asteroid using an iterator, in order to remove any destroyed asteroids
    for (auto asteroidIter = asteroids.begin(); asteroidIter != asteroids.end();)
    {
        // If the asteroid is not alive, remove it from the vector
        if (!asteroidIter->get()->isAlive())
        {
            // Remove asteroid from vector
            asteroidIter = asteroids.erase(asteroidIter);

            // Resort asteroid vector as data has been removed
            sortAsteroids();
        }
        else
        {
            // Increment iterator if asteroid is not removed to continue onto next asteroid in vector
            asteroidIter++;
        }
    }


}

// Sort asteroids
void AsteroidManager::sortAsteroids()
{
    
    // Sort all asteroids in vector based on depth, providing a fake 3D appearance

    // Using stable sort from the C++ standard library to sort all asteroids in the vector, and
    // using a lambda function which takes in adjacent asteroids and determines their order in
    // the vector by comparing their depth.

    // Stable sort is used rather than regular sort, as while it is slower, it ensures that identical
    // values (i.e. when 2 asteroids are at the same depth) will retain their order on each sort.
    // This prevents "Z-fighting"

    std::stable_sort(asteroids.begin(), asteroids.end(),
        [](std::unique_ptr<Asteroid> const& asteroid, std::unique_ptr<Asteroid> const& asteroid2)
        {
            return asteroid->getDepth() > asteroid2->getDepth();
        }
    );

}

// Draw asteroids
void AsteroidManager::drawAsteroids(sf::RenderWindow& window)
{
    // Iterate over all asteroids in vector and draw them
    for (std::unique_ptr<Asteroid>& asteroid : asteroids)
    {
        // Draw asteroid
        asteroid->draw(window);
    }
}

// Reset asteroids
void AsteroidManager::reset()
{
    // Delete all asteroids in vector
    asteroids.clear();
}

// Asteroid vector getter function
std::vector<std::unique_ptr<Asteroid>>& AsteroidManager::getAsteroids()
{
    // Return reference to asteroids vector
    return asteroids;
}
