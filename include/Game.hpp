//
// Game.hpp
//
// An instance of this is created in the main function
// The whole game is then ran inside of this class
//


#ifndef GAME_HPP
#define GAME_HPP

#include <SFML/Graphics.hpp>
#include <json.hpp>
#include <fstream>
#include <cmath>
#include <iostream>
#include <vector>

#include "Constants.hpp"
#include "Camera.hpp"

#include "Objects/PlayerShip.hpp"
#include "Objects/SpaceStation.hpp"
#include "Objects/ItemPickupType.hpp"
#include "Objects/HealthBar.hpp"

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
#include "Manager/MissionManager.hpp"

#include "UI/UIButton.hpp"
#include "UI/UISellItemBar.hpp"
#include "UI/UIButtonGroup.hpp"

enum class GameState
{
    MainMenu,
    InSpace,
    InStation
};

enum class StationMenuState
{
    Main,
    Upgrades,
    Market,
    Missons,
    Level
};

enum class LoadDataSuccess
{
    SUCCESSFUL,
    NO_FILE,
    CORRUPT_FILE
};

class Game
{

public:
    Game();

    bool initialise();

    void mainLoop();

private:
    void initUI();

    void inMainMenuLoop();
    void inSpaceLoop();
    void inStationLoop();

    void changeState(GameState newState);

    float distanceSqToStation();

    LoadDataSuccess loadData();
    void saveData();

    void newGame();
    void loadGame();
    void resetGame();

private:
    sf::RenderWindow window;
    sf::Image iconImage;
    sf::View view;

    GameState gameState;
    StationMenuState stationMenuState;
    
    sf::Vector2i titleBackgroundSubRectPos;
    PlanetRenderer titlePlanetRenderer;

    sf::Clock clock;
    PlanetRenderer mainPlanetRenderer;
    SpaceStation spaceStation;
    PlayerShip playerShip;

    HealthBar playerHealthBar;
    HealthBar levelBar;

    UIButtonGroup titleButtons;
    UIButtonGroup pauseMenuButtons;

    UIButtonGroup stationMenuButtons;
    UIButtonGroup stationUpgradeButtons;
    UIButtonGroup stationMarketButtons;
    UIButtonGroup stationMissionButtons;
    UIButtonGroup stationLevelButtons;

    std::string selectedMissionTitle, selectedMissionDesc;

    static constexpr float STATION_MAX_RANGE = 320;
    bool inStationRange;

    bool showUIRing;
    bool paused;

    bool loadDataError;
    LoadDataSuccess loadDataErrorType;

};

#endif