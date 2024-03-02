// Game.hpp

#ifndef GAME_HPP
#define GAME_HPP

// Include libraries
#include <SFML/Graphics.hpp>
#include <PhysFsStream.hpp>
#include <json.hpp>
#include <magic_enum.hpp>
#include <fstream>
#include <cmath>
#include <iostream>
#include <vector>

// Include headers
#include "Constants.hpp"
#include "Camera.hpp"
#include "Recipes.hpp"
#include "PlanetTravelData.hpp"

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
#include "Manager/UpgradeManager.hpp"
#include "Manager/UIRingManager.hpp"
#include "Manager/EnemyShipManager.hpp"
#include "Manager/SoundManager.hpp"
#include "Manager/MissionManager.hpp"

#include "UI/UIButton.hpp"
#include "UI/UITradeItemBar.hpp"
#include "UI/UIButtonGroup.hpp"

// Enum containing all game states
enum class GameState
{
    MainMenu,
    InSpace,
    InStation,
    Travelling
};

// Enum containing all states of the space station UI
enum class StationMenuState
{
    Main,
    Upgrades,
    Market,
    Forge,
    Missions,
    Level,
    Travel
};

// Enum containing all possible scenarios when attempting to load save data
enum class LoadDataSuccess
{
    SUCCESSFUL,
    NO_FILE,
    CORRUPT_FILE
};

// Declare game class
// An instance of this is created in the main function
// The whole game is then ran inside of this class
class Game
{

// Public class functions
public:
    // Constructor
    Game();

    // Initialise game, loading all assets into memory and initialising variables
    bool initialise();

    // Game loop, where the actual game runs
    void mainLoop();

    // Deinitialise game, by freeing all assets from memory
    void deinitialise();

// Private class functions
private:
    // Initialise all UI elements
    void initUI();

    // Game loop for main menu game state
    void inMainMenuLoop(float deltaTime);

    // Game loop for in space game state
    void inSpaceLoop(float deltaTime);

    // Game loop for in space station game state
    void inStationLoop(float deltaTime);

    // All game loops for separate space station UI states
    void inStationMainSubloop(sf::Vector2f mousePos, bool leftMousePressed);
    void inStationUpgradesSubloop(sf::Vector2f mousePos, bool leftMousePressed);
    void inStationMarketSubloop(sf::Vector2f mousePos, bool leftMousePressed);
    void inStationForgeSubloop(sf::Vector2f mousePos, bool leftMousePressed);
    void inStationMissionsSubloop(sf::Vector2f mousePos, bool leftMousePressed);
    void inStationLevelSubloop(sf::Vector2f mousePos, bool leftMousePressed);
    void inStationTravelSubloop(sf::Vector2f mousePos, bool leftMousePressed);

    // Game loop for travelling game state
    void travellingLoop(float deltaTime);

    // Draw fade transition for transitioning between game states
    void drawGameStateTransition(float deltaTime);

    // Change game state
    void changeState(GameState newState);

    // Used to update the selection of planets the player can travel to
    // by using the space station UI
    void updatePlanetSelection();

    // Changes current planet and resets necessary variables
    void travelToPlanet(PlanetType planet);

    // Draw mission progress UI element
    void drawMissionProgress(float deltaTime);

    // Calculate square distance between player ship and space station
    float distanceSqToStation();

    // Load save data
    LoadDataSuccess loadData();
    // Save current game data to file
    void saveData();

    // Start a new game
    void newGame();
    // Load game, by loading save data
    void loadGame();
    // Reset game variables, such as asteroids, enemies, and bullets
    void resetGame();

// Private member variables
private:
    // Variable storing game window
    sf::RenderWindow window;
    // Variable storing icon of game window
    sf::Image iconImage;
    // Variable storing game "view" (area that can be seen on screen)
    sf::View view;

    // Variable storing current game state
    GameState gameState;
    // Variable storing the game state being transitioned to
    GameState targetGameState;
    // Variable storing time of game state fade transition
    float gameStateTransitionTimer;

    // Variable storing current state in space station UI
    StationMenuState stationMenuState;

    // Variable storing rectangle area of space background to draw on title screen (randomised area)
    sf::Vector2i titleBackgroundSubRectPos;
    // Variable storing planet renderer object for planet drawn on title screen
    PlanetRenderer titlePlanetRenderer;

    // Variable storing clock object to keep track of frametime
    sf::Clock clock;
    // Variable storing planet renderer object for planet drawn in game
    PlanetRenderer mainPlanetRenderer;
    // Variable storing space station object
    SpaceStation spaceStation;
    // Variable storing player ship object
    PlayerShip playerShip;
    // Variable storing current planet type
    PlanetType currentPlanet;

    // Variable storing player health bar object
    HealthBar playerHealthBar;
    // Variable storing player level bar object
    HealthBar levelBar;
    // Variable storing mission progress bar object
    HealthBar missionProgress;

    // Button group for title screen buttons
    UIButtonGroup titleButtons;
    // Button group for pause menu buttons
    UIButtonGroup pauseMenuButtons;

    // Button groups for each space station UI state
    UIButtonGroup stationMenuButtons;
    UIButtonGroup stationUpgradeButtons;
    UIButtonGroup stationMarketButtons;
    UIButtonGroup stationMissionButtons;
    UIButtonGroup stationLevelButtons;
    UIButtonGroup stationTravelButtons;

    // Variable storing the currently selected mission in the space station UI
    int selectedMission;
    // Variable storing vertical scroll amount for UI elements
    int uiScrollCount;

    // Constant storing range in which the player can interact with the space station
    static constexpr float STATION_MAX_RANGE = 320;
    // Variable storing whether the player is within the space station range
    bool inStationRange;

    // Variable storing current time player has been travelling to another planet for
    float travelTime;

    // Variable storing whether or not to draw the UI navigation ring
    bool showUIRing;
    // Variable storing whether the game is paused or not
    bool paused;

    // Variable storing whether an error has occured when attempting the load save data
    bool loadDataError;
    // Variable storing what type of error has occursed when attempting to load save data, if error has occured
    LoadDataSuccess loadDataErrorType;

};

#endif