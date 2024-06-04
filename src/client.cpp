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


using namespace std;

int main (int args, char ** argv){

  int port = 8080;
  string adress = "127.0.0.1";  

  cout << "[info] ip adress: "<< adress << " port: " << port << endl;
  sockaddr_in server_addr;
  
  int sock_fd = socket(AF_INET, SOCK_STREAM, 0);
  if (sock_fd < 0) {
    cerr << "[ERROR] Socket cannot be created!\n";
    return 1;
  }
  cout << "[INFO] Socket has been created.\n";


  memset((char*)&server_addr, 0, sizeof(server_addr));
  server_addr.sin_family = AF_INET;
  server_addr.sin_port = htons(port);
  inet_pton(AF_INET, adress.c_str(), &server_addr.sin_addr);
  

  if (connect(sock_fd, (sockaddr*)&server_addr, sizeof(server_addr)) < 0) {
    cerr << "Connection cannot be established!\n";
    return 1;
  }
  cout << "[INFO] Connection established.\n";

  string buf = "Hello from client!";
  

  send(sock_fd, buf.c_str(), (size_t)buf.length(), 0);

  close(sock_fd);

    return 0;   
}