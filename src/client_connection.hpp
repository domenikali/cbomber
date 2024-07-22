#ifndef CLIENT_CONNECTION_H
#define CLIENT_CONNECTION_H

#include "domes_library.hpp"
#include "header.hpp"
#include "utils.hpp"
#include <cstring>

#include <iostream>
#include <arpa/inet.h>
#include <unistd.h>
#include <net/if.h>


/**
 *  @brief create a fd for a client socket
 *  @param port port number 
 *  @param adress the adress of the server
 *  @param tcp_server_sock pointer server socket fd that get created
 *  @return the sockaddr_in structure of the server
 */
sockaddr_in connect_to_server(const int port, const string adress, int * tcp_server_sock);

/**
 *  @brief create a fd for a udp ipv6 client socket
 *  @param ipv6 the adress of the server as char array
 *  @param port port number 
 *  @return the sockaddr_in structure of the server
 */
struct sockaddr_in6 create_udp_client_sockaddr(const char* ipv6,int port);

/**
 *  @brief create a fd for a udp ipv6 client socket
 *  @return the fd 
 */
int create_mcast_sock();

/**
 *  @brief create a sockaddr_in6 structure for the mcast
 *  @param mcast_sock the mcast socket
 *  @param mcast_port the mcast port
 *  @return the sockaddr_in6 structure
 */
struct sockaddr_in6 create_mcast_sockaddr(int mcast_sock,int mcast_port);

/**
 *  @brief inscribe to the mcast group
 *  @param mcast_client_sock the mcast socket
 *  @param ip the ip of the mcast group
 */
void inscribe_to_mcast(int mcast_client_sock, char * ip);




#endif 