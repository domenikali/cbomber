#include "config.hpp"

Config::Config(){
    std::ifstream inputFile("config");

    if (!inputFile) {
        std::cerr << "Unable to open file" << std::endl;
        return; // Return with an error code
    }

    std::string line;
    // Read the file line by line
    while (std::getline(inputFile, line)) {
        // Parse each line
        if (line.find("SERVER_IP6") == 0) {
            this->serverIP6Adress = line.substr(line.find(" ") + 1);
        } else if (line.find("SERVER_IP4") == 0) {
            this->serverIP4Adress = line.substr(line.find(" ") + 1);
        } else if(line.find("SERVER_PORT") == 0){
            this->serverPort = std::stoi(line.substr(line.find(" ") + 1));
        }
    }

    // Close the file
    inputFile.close();
}