#ifndef GAME_HPP
#define GAME_HPP

#include <SFML/Graphics.hpp>
#include <cmath>
#include <iostream>

#include "Constants.hpp"
#include "Camera.hpp"
#include "Objects/PlayerShip.hpp"
#include "Objects/SpaceStation.hpp"
#include "Renderer/PlanetRenderer.hpp"
#include "Renderer/TextRenderer.hpp"
#include "Manager/TextureManager.hpp"
#include "Manager/BulletManager.hpp"
#include "Manager/AsteroidManager.hpp"
#include "Manager/ItemPickupManager.hpp"
#include "Manager/InventoryManager.hpp"
#include "Manager/UIRingManager.hpp"
#include "Manager/EnemyShipManager.hpp"
#include "Manager/SoundManager.hpp"

enum class GameState
{
    InSpace,
    InStation
};

class Game
{

public:
    Game();

    bool initialise();

    void mainLoop();

private:
    void inSpaceLoop();
    void inStationLoop();

    float distanceSqToStation();

private:
    sf::RenderWindow window;
    sf::Image iconImage;

    GameState gameState;

    sf::Clock clock;
    PlanetRenderer mainPlanetRenderer;
    SpaceStation spaceStation;
    PlayerShip playerShip;

    static constexpr float STATION_MAX_RANGE = 320;
    bool inStationRange;

    bool showUIRing;

};

#endif