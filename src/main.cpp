#include <iostream>
#include <physfs.h>
#include "Game.hpp"

int main(int argc, char* argv[])
{

    PHYSFS_init(argv[0]);
    PHYSFS_mount("data.bin", NULL, 1);

    Game game;
    if (!game.initialise())
    {
        std::cout << "ERROR: Failed to initialise game" << std::endl;
        return -1;
    }

    game.mainLoop();

    game.deinitialise();

    PHYSFS_deinit();

    return 0;
}