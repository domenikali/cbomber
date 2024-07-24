#ifndef ACTION_H
#define ACTION_H

#include "domes_library.hpp"
#include "header.hpp"
#include <iostream>
#include <netinet/in.h>
#include <arpa/inet.h>


/**
 * @brief class to handle the action of the clients
 */
class Action{
    private:
        Header header;
        uint16_t action;
    public:
    Action (Header header, uint16_t action);
    Action (const char * serialized_action);

    Header get_header(){ return header;};
    uint16_t get_action(){ return ntohs(action);};
    void set_header(Header header){ this->header = header;};
    void set_action(uint16_t action){ this->action = htons(action);};

    char * serialize(ssize_t * packet_size);
    int send_action(const int sock_fd);
    static Action recv_action(const int sock_fd);
    std::string to_string();
};


#endif