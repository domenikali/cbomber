#ifndef HEADER_H
#define HEADER_H

#include "domes_library.hpp"
#include <iostream>
#include <cstring>
#include <cstdint>
#include <sys/socket.h>


/**
 *  @brief class to handle the header of the packets
 *  @details the header is a 16 bit number that contains the code of the packet, the id of the client and the team of the client
 *  @details the header is divided in 13 bits for the code, 2 bits for the id and 1 bit for the team
 */
class Header{
  private:
    uint16_t head; // 13 bits for code, 2 bit for id, 1 bit for team

  public:
    Header(uint16_t code, uint8_t id, uint8_t team);
    Header(const char * serialized_header);
    Header()=default;
    uint16_t get_header(){ return head;};
    uint16_t get_code();
    uint8_t get_id();
    uint8_t get_team();

    /**
     * @brief decode the header into separet variables passed by reference
     * @param code the code of the packet
     * @param id the id of the client
     * @param team the team of the client
    */
    void decode(uint16_t * code, uint8_t * id, uint8_t * team);
    
    void set_code(uint16_t code);
    void set_id(uint8_t id);
    void set_team(uint8_t team);
    
    /**
     * @brief check if the header sent is ok (code = 0) or is an error (code = 1)
     * @return true if the header is ok, false otherwise
    */
    bool is_valid();
    
    /**
     * @brief serialize the header into a char array
     * @details the serialized header is 2 bytes string
     * @param packet_size the size of the serialized header
     * @return the serialized header
    */
    char * serialize(ssize_t * packet_size);
    
    /**
     * @brief send the header to a socket (could be tcp or udp)
     * @param sock_fd the socket file descriptor
     * @return the 0 if the header was sent successfully, -1 otherwise
    */
    int send_header(const int sock_fd);

    /**
     * @brief receive the header from a socket (could be tcp or udp)
     * @details recived the serialized header, deserialize it and set the header
     * @param sock_fd the socket file descriptor
     * @return the 0 if the header was received successfully, -1 otherwise
    */
    static Header recv_header(const int sock_fd);

    /**
     * @brief create an error header
     * @return the error header
    */
    static Header error_header();

    /**
     * @brief create a success header
     * @return the success header
    */
    static Header success_header();

    /**
     * @brief create a string representation of the header
     * @return return the string representation of the header
    */
    std::string to_string();
  };
 


#endif