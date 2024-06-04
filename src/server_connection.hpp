#ifndef SERVER_CONNECTION_H
#define SERVER_CONNECTION_H

#include "utils.hpp"
#include <iostream>

using namespace std;

#include <sys/socket.h>   
#include <arpa/inet.h>


int create_server_socket(int port);

sockaddr_in accept_client(int tcp_server_sock, int *sock_client);

#endif