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



int main (int args, char ** argv){

  int port = 8080;
  string adress = "127.0.0.1";    

  int sock_fd;
  connect_to_server(port, adress , &sock_fd);

  string buf = "Hello from client!";
  

  send(sock_fd, buf.c_str(), (size_t)buf.length(), 0);

  close(sock_fd);

    return 0;   
}