#ifndef SERVER_CONNECTION_H
#define SERVER_CONNECTION_H

#include "domes_library.hpp"
#include "packets.hpp"
#include <iostream>


#include <sys/socket.h>   
#include <arpa/inet.h>

/**
 *  @brief create a fd for a server socket
 *  @param port port number 
 *  @return the fd created
 */
int create_server_socket(const int port);

/**
 *  @brief accept a client connection
 *  @param tcp_server_sock the server socket fd
 *  @param sock_client pointer to the clinet socket that get created
 *  @return the client sockaddr_in strcture
*/
sockaddr_in accept_client(const int tcp_server_sock, int *sock_client);

#endif