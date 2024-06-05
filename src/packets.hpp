#ifndef PACKETS_H
#define PACKETS_H

#include <iostream>
#include <string>

using std::string;

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
    string to_string();
};


#endif