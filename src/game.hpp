#ifndef GAME_H
#define GAME_H

#include <iostream>
#include <fstream>
#include <string>
#include "domes_library.hpp"
#include "header.hpp"

/**
 * @brief class to handle the game configuration
 * @details the game configuration is loaded from a file called config
 * @details the file contains the grid height and width
 * @details the grid is a square grid
 */
class Game{
    private:
        uint8_t gridHeight;
        uint8_t gridWidth;
        uint8_t **grid;

    public:
        Game();
        Game(uint8_t gridHeight, uint8_t gridWidth);
        int getGridHeight();
        int getGridWidth();
        void setGridHeight(uint8_t gridHeight){
            this->gridHeight = gridHeight;
        };
        void setGridWidth(uint8_t gridWidth){
            this->gridWidth = gridWidth;
        };
        /**
         * @brief reload the configuration from the file config
         */
        void reloadConfig();
        void fillGrid();
        /**
         * @brief send the grid via TCP packet to client
         * @param socket the socket to send the grid
         * @return 0 if the grid was sent successfully, -1 otherwise
         */
        int send_tcp_grid(const int socket);
        char * serialize_grid();
        static Game deserialize_grid(char * serialize_grid);
        static Game recv_grid(const int socket);
        void printGrid();
        std::string to_string();
};



#endif