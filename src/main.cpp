#include <iostream>
#include "Game.hpp"

int main()
{

    Game game;
    if (!game.initialise())
    {
        std::cout << "ERROR: Failed to initialise game" << std::endl;
        return -1;
    }
    game.mainLoop();

    return 0;
}