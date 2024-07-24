#include "game_tests.hpp"

void testReloadConfig(){
    
    std::cout << "Testing reloadConfig... ";
    Game game;
    int gridHeight = 0;
    int gridWidth = 0;

    std::ifstream inputFile("config");

    if (!inputFile) {
        std::cerr << "Unable to open file" << std::endl;
        return; 
    }

    std::string line;
    while (std::getline(inputFile, line)) {
        if (line.find("GRID_H") == 0) {
            gridHeight = std::stoi(line.substr(line.find(" ") + 1));
        } else if (line.find("GRID_W") == 0) {
            gridWidth = std::stoi(line.substr(line.find(" ") + 1));
        }
    }

    // Close the file
    inputFile.close();

    assert(game.getGridHeight() == gridHeight);
    assert(game.getGridWidth() == gridWidth);

    std::cout <<GREEN<< "OK" <<RESET<< std::endl;

}