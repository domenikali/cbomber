#ifndef CLIENT_CONNECTION_H
#define CLIENT_CONNECTION_H

#include "domes_library.hpp"
#include "header.hpp"
#include "utils.hpp"
#include <cstring>

#include <iostream>
#include <arpa/inet.h>

/**
 *  @brief create a fd for a client socket
 *  @param port port number 
 *  @param adress the adress of the server
 *  @param tcp_server_sock pointer server socket fd that get created
 *  @return the sockaddr_in structure of the server
 */
sockaddr_in connect_to_server(const int port, const string adress, int * tcp_server_sock);




#endif 