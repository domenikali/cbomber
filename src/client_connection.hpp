#ifndef CLIENT_CONNECTION_H
#define CLIENT_CONNECTION_H

#include "utils.hpp"
#include <cstring>

#include <iostream>
using namespace std;
#include <arpa/inet.h>

sockaddr_in connect_to_server(int port, string adress, int * tcp_server_sock);




#endif 