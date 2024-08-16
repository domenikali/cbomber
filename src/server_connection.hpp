#ifndef SERVER_CONNECTION_H
#define SERVER_CONNECTION_H

#include "header.hpp"
#include "utils.hpp"
#include "match_info.hpp"
#include "domes_library.hpp"
#include "game.hpp"
#include "action.hpp"
#include <iostream>


#include <sys/socket.h>   
#include <arpa/inet.h>
#include <mutex>
#include <stack>
#include <net/if.h>
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

/**
 *  @brief queue a client to the lobby
 *  @param client_sock the client socket fd
*/
void queue_client(const int client_sock);

/**
 *  @brief lobby for a match
 *  @param mode the mode of the match
*/
void lobby(const int mode);

/**
 *  @brief create a new match infos
 *  @details create a new match info with a random mcast adress and ports for multicast and udp communication
 *  @return the match
*/
Match_info init_match();

/**
 * @brief create a new mcast adress
 * @details create a new ipv6 adress randomly ad exception of the first 16 bit describing the multicast adress
 * @return the adress
 */
char * new_mdiff_adress();
#endif