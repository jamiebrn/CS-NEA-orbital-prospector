#ifndef GAME_HPP
#define GAME_HPP

#include <SFML/Graphics.hpp>
#include <cmath>
#include <iostream>
#include <functional>
#include <vector>

#include "Constants.hpp"
#include "Camera.hpp"
#include "Objects/PlayerShip.hpp"
#include "Objects/SpaceStation.hpp"
#include "Objects/ItemPickupType.hpp"
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
#include "UI/UIButton.hpp"
#include "UI/UISellItemBar.hpp"

enum class GameState
{
    MainMenu,
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
    void inMainMenuLoop();
    void inSpaceLoop();
    void inStationLoop();

    void changeState(GameState newState);

    float distanceSqToStation();
    void sellItem(ItemPickupType type);

private:
    sf::RenderWindow window;
    sf::Image iconImage;
    sf::View view;

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