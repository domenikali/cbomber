#include "action.hpp"

/**
 * @brief constructor
 * @param header the header of the action
 * @param action the action
 */
Action::Action(Header header, uint16_t action){
    this->header = header;
    this->action = htons(action);
}

/**
 * @brief constructor
 * @param serialized_action the serialized action
 */
Action::Action(const char * serialized_action){
    int offset = 0;
    memcpy(&header, serialized_action, 2);
    offset += 2;
    memcpy(&action, serialized_action + offset, 2);
}

/**
 * @brief serialize the action
 * @param packet_size the size of the packet
 * @return the serialized action
 */
char * Action::serialize(ssize_t * packet_size){
    char * serialized = new char[4];
    int offset = 0;
    memcpy(serialized, &header, 2);
    offset += 2;
    memcpy(serialized + offset, &action, 2);
    *packet_size = 4;
    return serialized;
}

/**
 * @brief send the action vai tcp
 * @param sock_fd the socket file descriptor
 * @return 0 on success, -1 on failure
 */
int Action::send_action(const int sock_fd){
    ssize_t packet_size=sizeof(char)*4;
    char * serialized_packet = serialize(&packet_size);
    ssize_t total = 0, bytes_sent=0;
    while(bytes_sent < packet_size){
        bytes_sent = send(sock_fd, serialized_packet + bytes_sent, packet_size - bytes_sent, 0);
        if(bytes_sent == -1){
            print(ERROR, "Error sending packet");
            return -1;
        }
        
        total += bytes_sent;
    }

    delete[] serialized_packet;
    print(INFO, "Action sent successfully");
    return 0;
}

/**
 * @brief receive the action via tcp
 * @param sock_fd the socket file descriptor
 * @return the received action
 */
Action Action::recv_action(const int sock_fd){
    ssize_t packet_size = 4;
    char * serialized_packet = new char[4];
    ssize_t total = 0, bytes_recv=0;
    while(total < packet_size){
        bytes_recv = recv(sock_fd, serialized_packet + total, packet_size - total, 0);
        if(bytes_recv == -1){
            print(ERROR, "Error receiving packet");
            exit(EXIT_FAILURE);
        }
        total += bytes_recv;
    }
    Action action(serialized_packet);
    delete[] serialized_packet;
    print(INFO, "Action received successfully");
    return action;
}

/**
 * @brief convert the action to string
 * @return the string representation of the action
 */
std::string Action::to_string(){
    std::string str = "Action: ";
    str += header.to_string();
    str += " Action: ";
    str += std::to_string(ntohs(action));
    return str;
}


