#include "game.hpp"

Game::Game(){
    reloadConfig();
}

Game::Game(uint8_t gridHeight, uint8_t gridWidth){
    this->gridHeight = gridHeight;
    this->gridWidth = gridWidth;
    this->grid = new uint8_t*[gridHeight];
    for(int i = 0; i < gridHeight; i++){
        grid[i] = new uint8_t[gridWidth];
    }
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

    grid = new uint8_t*[gridHeight];
    for(int i = 0; i < gridHeight; i++){
        grid[i] = new uint8_t[gridWidth];
    }
    fillGrid();
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
            std::cout << std::to_string(grid[i][j]) << " ";
        }
        std::cout << std::endl;
    }
}

int Game::send_tcp_grid(const int socket){
    char * serialized_grid = serialize_grid();
    ssize_t packet_size = gridHeight * gridWidth + 4;
    ssize_t total = 0, bytes_sent=0;
    while(bytes_sent < packet_size){
        bytes_sent = send(socket, serialized_grid + bytes_sent, packet_size - bytes_sent, 0);
        if(bytes_sent == -1){
            std::cerr << "Error sending packet" << std::endl;
            return -1;
        }
        total += bytes_sent;
    }
    delete[] serialized_grid;
    return 0;
}

char * Game::serialize_grid(){
    char * serialized_grid = new char[this->gridHeight * this->gridWidth + 4];
    Header header = Header::success_header();  
    int offset = 0;
    memcpy(serialized_grid, &header, sizeof(uint16_t));
    offset +=2;
    memcpy (serialized_grid + offset, &this->gridHeight, sizeof(uint8_t));
    offset +=1;
    memcpy (serialized_grid + offset, &this->gridWidth, sizeof(uint8_t));
    
    for(int i = 0 ; i< this->gridHeight; i++){
        for(int j = 0; j < this->gridWidth; j++){
            offset +=1;
            memcpy(serialized_grid + offset, &this->grid[i][j], sizeof(uint8_t));
        }
    }
    return serialized_grid;

}

Game Game::deserialize_grid(char * serialize_grid){
    
    ssize_t offset = 2;
    uint8_t gridHeight=serialize_grid[offset];
    
    
    
    offset +=1;
    uint8_t gridWidth=serialize_grid[offset];
     
    Game game = Game(gridHeight, gridWidth);
    
    game.grid = new uint8_t*[game.getGridHeight()];
    for(int i = 0; i < game.getGridWidth(); i++){
        game.grid[i] = new uint8_t[game.getGridWidth()];
    }
    for(int i = 0 ; i < game.getGridHeight(); i++){
        for(int j = 0; j < game.getGridWidth(); j++){ 
            offset +=1;
            memcpy(&game.grid[i][j], serialize_grid + offset, sizeof(uint8_t));
        }
    }
    return game;
}

std::string Game::to_string(){
    std::string str = "Grid Height: " + std::to_string(gridHeight) + "\n";
    str += "Grid Width: " + std::to_string(gridWidth) + "\n";
    for(int i = 0 ; i < gridHeight; i++){
        for(int j = 0; j < gridWidth; j++){
            str += std::to_string(grid[i][j]) + " ";
        }
        str += "\n";
    }
    return str;
}

