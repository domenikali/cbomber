#ifndef MATCH_INFO_H
#define MATCH_INFO_H

#include "domes_library.hpp"
#include "header.hpp"
#include <iostream>
#include <netinet/in.h>
#include <arpa/inet.h>


/**
 * @brief class to handle the match info
 * @details the match info contains the header of the packet, the udp port, the mcast port and the mcast address
 * @details in particular the ports are uint16_t in network order, the mcast address is an array of 16 bytes containing each an hex
 * @details the match info is used to send the information of the match to the clients
*/
class Match_info{
  private:
    Header header;
    uint16_t udp_port;
    uint16_t mcast_port;
    uint8_t mcast_addr[16];
    
  public:
    Match_info(Header header, uint16_t udp_port, uint16_t mcast_port, std::string mcast_addr);
    Match_info(const char * serialized_match_info);
    
    Header get_header(){ return header;};
    uint16_t get_udp_port(){ return ntohs(udp_port);};
    uint16_t get_mcast_port(){return ntohs(mcast_port);};
    uint8_t * get_mcast_addr_uint(){return mcast_addr;};
    char * get_mcast_addr_str();

    void set_header(Header header){ this->header = header;};
    void set_udp_port(uint16_t udp_port){ this->udp_port = htons(udp_port);};
    void set_mcast_port(uint16_t mcast_port){this->mcast_port = htons(mcast_port);};
    void set_mcast_addr_uint(uint8_t mcast_addr[16]){memcpy(this->mcast_addr, mcast_addr, 16);};
    void set_mcast_addr_str(std::string mcast_addr){inet_pton(AF_INET6, mcast_addr.c_str(), this->mcast_addr);};
    
    char * serialize(ssize_t * packet_size);
    int send_match_info(const int sock_fd);
    static Match_info recv_match_info(const int sock_fd);
    std::string to_string();

};

#endif