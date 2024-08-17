#ifndef CONFIG_H
#define CONFIG_H

#include "domes_library.hpp"
#include <fstream>


/**
 * @brief class to handle the game configuration
 * @details server ips and ports
 */

class Config{
  private:
    std::string serverIP4Adress;
    std::string serverIP6Adress;
    int serverPort;

    
  public:
    Config();
    std::string getServerIP4Adress(){return this->serverIP4Adress;};
    int getServerPort(){return this->serverPort;};
    std::string getServerIP6Adress(){return this->serverIP6Adress;};
};

#endif