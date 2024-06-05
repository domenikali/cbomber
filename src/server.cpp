#include "packets.hpp"
#include "server_connection.hpp"
#include "utils.hpp"

#include <iostream>
#include <ctime>
#include <cstdlib>

#include <sys/socket.h>      
#include <netinet/in.h>    
#include <cstring>           
#include <unistd.h>  

#include <sys/types.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <type_traits>



int main (int args, char ** argv){
  int port = 8080;

  int tcp_server_sock = create_server_socket(port);

  while(true){
    int sock_client ;
    accept_client(tcp_server_sock, &sock_client);

    Header header(0,0,0);
    header.recv_header(sock_client);
    close(sock_client);
  }
 
  
  

  close(tcp_server_sock);
  

  return 0;
}