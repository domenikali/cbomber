#ifndef GAME_H
#define GAME_H

#include <iostream>
#include <fstream>
#include <string>
#include "domes_library.hpp"

/**
 * @brief class to handle the game configuration
 * @details the game configuration is loaded from a file called config
 * @details the file contains the grid height and width
 * @details the grid is a square grid
 */
class Game{
    private:
        int gridHeight;
        int gridWidth;
        int **grid;
    public:
        Game();
        int getGridHeight();
        int getGridWidth();
        /**
         * @brief reload the configuration from the file config
         */
        void reloadConfig();
        void fillGrid();
        void printGrid();
};



#endif