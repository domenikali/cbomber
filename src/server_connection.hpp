#ifndef SERVER_CONNECTION_H
#define SERVER_CONNECTION_H

#include "header.hpp"
#include "utils.hpp"
#include "match_info.hpp"
#include "domes_library.hpp"
#include <iostream>


#include <sys/socket.h>   
#include <arpa/inet.h>
#include <mutex>
#include <stack>
#include <thread>   

typedef struct{
  int tcp_socket;
  int id;
}Player;



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

Match_info init_match();

/**
 * @brief create a new mcast adress
 * @details create a new ipv6 adress randomly ad exception of the first 16 bit describing the multicast adress
 * @return the adress
 */
char * new_mdiff_adress();
#endif