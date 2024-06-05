#include "client_connection.hpp"

sockaddr_in connect_to_server(const int port, const string adress, int * tcp_server_sock){
  *tcp_server_sock = socket(AF_INET, SOCK_STREAM, 0);
  if (*tcp_server_sock < 0) {
    print(ERROR, "Socket cannot be created!");
    exit(EXIT_FAILURE);
  }
  print(INFO, "Socket created.");

  sockaddr_in server_addr;
  memset((char*)&server_addr, 0, sizeof(server_addr));
  server_addr.sin_family = AF_INET;
  server_addr.sin_port = htons(port);
  inet_pton(AF_INET, adress.c_str(), &server_addr.sin_addr);
  

  if (connect(*tcp_server_sock, (sockaddr*)&server_addr, sizeof(server_addr)) < 0) {
    print(ERROR, "Connection failed!");
    exit(EXIT_FAILURE);
  }
  print(INFO, "Connected to server.");
  return server_addr;

}