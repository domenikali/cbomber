#include "server_connection.hpp"

int create_server_socket(int port){

  //init socket
  int tcp_server_sock = socket(AF_INET, SOCK_STREAM, 0);
  if (tcp_server_sock < 0) {
    print(ERROR,"Socket cannot be created.");
    exit(EXIT_FAILURE);
  }
  print(INFO,"Socket is created.");

  const int enable = 1;
  if (setsockopt(tcp_server_sock, SOL_SOCKET, SO_REUSEADDR, &enable, sizeof(int)) < 0)
    print(ERROR,"setsockopt(SO_REUSEADDR) failed");

  sockaddr_in server_addr;
  server_addr.sin_family = AF_INET;
  server_addr.sin_port = htons(port);
  server_addr.sin_addr.s_addr = INADDR_ANY;
  print(INFO,"Server address is created.");
  
  if (bind(tcp_server_sock, (sockaddr *)&server_addr, sizeof(server_addr)) < 0) {
    print(ERROR,"Socket cannot be binded.");
    exit(EXIT_FAILURE);
  }
  print(INFO,"Socket is binded.");

  if (listen(tcp_server_sock, 0) < 0) {
    print(ERROR,"Socket cannot listen.");
    exit(EXIT_FAILURE);
  }
  print(INFO,"Socket is listening.");
  return tcp_server_sock;
}

sockaddr_in accept_client(int tcp_server_sock, int *sock_client){
  sockaddr_in client_addr;
  socklen_t client_addr_size = sizeof(client_addr); 
  
  if ((*sock_client = accept(tcp_server_sock, (sockaddr*)&client_addr, &client_addr_size)) < 0) {
    print(ERROR,"Connections cannot be accepted for a reason.");
    exit(EXIT_FAILURE);
  }

  print(INFO,"A connection is accepted now.");
  return client_addr;
}

