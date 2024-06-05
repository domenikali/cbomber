#include "packets.hpp"
#include "client_connection.hpp"
#include "utils.hpp"

#include <iostream>
#include <ctime>
#include <cstdlib>

#include <sys/socket.h>      
#include <netinet/in.h>    
#include <cstring>           
#include <unistd.h>
#include <arpa/inet.h>
#include <bitset>


int main (int args, char ** argv){

  int port = 8080;
  string adress = "127.0.0.1";

  int game_mode = -1;
  while(game_mode==-1){
    string mode;
    cout << "Choose game mode: " << endl;
    cout << "1. Single player" << endl;
    cout << "2. Multiplayer" << endl;
    std::getline(std::cin, mode);
    if(mode == "1"){
      game_mode = 2;
    } else if(mode == "2"){
      game_mode = 3;
    } else {
      cout << "Invalid input" << endl;
    }
  }    

  Header require_match(game_mode, 0, 0);

  int tcp_server_socket;
  connect_to_server(port, adress , &tcp_server_socket);

  require_match.send_header(tcp_server_socket);

  close(tcp_server_socket);

    return 0;   
}