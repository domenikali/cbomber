#include "header.hpp"
#include "match_info.hpp"
#include "client_connection.hpp"
#include "utils.hpp"

#include <iostream>
#include <ctime>
#include <cstdlib>
#include <string>

#include <sys/socket.h>      
#include <netinet/in.h>    
#include <cstring>           
#include <unistd.h>
#include <arpa/inet.h>
#include <bitset>
#include <net/if.h>


int main (int args, char ** argv){

  int port = 8080;
  string adress = "127.0.0.1";

  int game_mode = -1;
  while(game_mode==-1){
    string mode;
    std::cout << "Choose game mode: \n" ;
    std::cout << "\t1. Single player\n";
    std::cout << "\t2. Multiplayer" << std::endl;
    std::getline(std::cin, mode);
    if(mode == "1"){
      game_mode = 2;
    } else if(mode == "2"){
      game_mode = 3;
    } else {
      std::cout << "Invalid input" << std::endl;
    }
  }    

  Header require_match(game_mode, 0, 0);

  int tcp_server_socket;
  connect_to_server(port, adress , &tcp_server_socket);

  require_match.send_header(tcp_server_socket);

  Header response = Header::recv_header(tcp_server_socket);
  print(INFO, "added to queue");

  Match_info match = Match_info::recv_match_info(tcp_server_socket);
  print(INFO, "Match: "+match.to_string());

  // Create UDP socket
  int udp_client_sock;
  if ((udp_client_sock = socket(AF_INET6, SOCK_DGRAM, 0)) < 0) {
    perror("Socket creation failed");
    exit(EXIT_FAILURE);
  }

  struct sockaddr_in6 udp_server_addr = create_udp_client_sockaddr("::1", match.get_udp_port()); 
  print(INFO, "UDP socket created");

  // Create mcast socket
  int mcast_client_sock = create_mcast_sock();

  struct sockaddr_in6 mdiff_server_addr = create_mcast_sockaddr(mcast_client_sock, match.get_mcast_port());
  
  inscribe_to_mcast(mcast_client_sock, match.get_mcast_addr_str());


  Header id_packet = Header::recv_header(tcp_server_socket);
  print(INFO, "match starting");

  close(tcp_server_socket);

  return 0;   
}