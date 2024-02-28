// Constants.hpp

#ifndef CONSTANTS_HPP
#define CONSTANTS_HPP

// Application information
#define WINDOW_WIDTH 1920
#define WINDOW_HEIGHT 1080
#define WINDOW_TITLE "Orbital Prospector"

// Resource paths
#define ICON_PATH "Icon/icon.png"
#define FONT_PATH "Font/ThaleahFat.ttf"

// Dimensions of game world
#define WORLD_WIDTH 10000.0f
#define WORLD_HEIGHT 10000.0f

// Values to divide different element positions by, to provide an illusion of depth
#define BACKGROUND_DEPTH_DIVIDE 6.0f
#define PLANET_DEPTH_DIVIDE 3.2f
#define SPACE_STATION_DEPTH_DIVIDE 1.4f

// Various game constants
#define ASTEROID_MAX 1000
#define STARTING_MAX_HEALTH 20
#define TRAVEL_TIME 3.0f
#define GAME_STATE_TRANSITION_TIME 0.3f

#endif