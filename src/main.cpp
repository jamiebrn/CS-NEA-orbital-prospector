// main.cpp

// Include libraries
#include <iostream>
#include <physfs.h>

// Include headers
#include "Game.hpp"

// Main function
int main(int argc, char* argv[])
{
    // Initialise PhysFS to argv[0], i.e. the executable path
    PHYSFS_init(argv[0]);
    // Mount the data archive containing all game data using PhysFS
    PHYSFS_mount("data.bin", NULL, 1);

    // Create an instance of the game class
    Game game;
    // Attempt to initialise game - if failed, output error message and return -1
    if (!game.initialise())
    {
        std::cout << "ERROR: Failed to initialise game" << std::endl;
        return -1;
    }

    // Run game loop
    game.mainLoop();
    
    // Deinitialise game, by unloading assets from memory
    game.deinitialise();

    // Deinitialise PhysFS
    PHYSFS_deinit();

    // Return 0 by default
    return 0;
}