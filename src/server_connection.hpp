#ifndef SERVER_CONNECTION_H
#define SERVER_CONNECTION_H

#include "header.hpp"
#include "utils.hpp"
#include "domes_library.hpp"
#include <iostream>


#include <sys/socket.h>   
#include <arpa/inet.h>
#include <mutex>
#include <stack>
#include <thread>   

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

void queue_client(const int client_sock);

void lobby(const int mode);

#endif