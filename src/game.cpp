#include "game.hpp"

Game::Game(){
    reloadConfig();
}

int Game::getGridHeight(){
    return gridHeight;
}

int Game::getGridWidth(){
    return gridWidth;
}

void Game::reloadConfig(){
    // Open the file
    std::ifstream inputFile("config");

    if (!inputFile) {
        std::cerr << "Unable to open file" << std::endl;
        return; // Return with an error code
    }

    std::string line;
    // Read the file line by line
    while (std::getline(inputFile, line)) {
        // Parse each line
        if (line.find("GRID_H") == 0) {
            gridHeight = std::stoi(line.substr(line.find(" ") + 1));
        } else if (line.find("GRID_W") == 0) {
            gridWidth = std::stoi(line.substr(line.find(" ") + 1));
        }
    }

    // Close the file
    inputFile.close();

    grid = new int*[gridHeight];
    for(int i = 0; i < gridHeight; i++){
        grid[i] = new int[gridWidth];
    }
}

void Game::fillGrid(){
    for(int i = 0 ; i < gridHeight; i++){
        for(int j = 0; j < gridWidth; j++){
            grid[i][j] = 0;
        }
    }

}

void Game::printGrid(){
    for(int i = 0 ; i < gridHeight; i++){
        for(int j = 0; j < gridWidth; j++){
            std::cout << grid[i][j] << " ";
        }
        std::cout << std::endl;
    }
}

