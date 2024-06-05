#include "packets.hpp"


Header::Header(uint16_t code, uint8_t id, uint8_t team){
    head = (code << 3) | (id << 1) | team;
}

Header::Header(const char * serialized_header){
    memcpy(&head, serialized_header, 2);
}

uint16_t Header::get_code(){
    return head >> 3;
}

uint8_t Header::get_id(){
    return (head >> 1) & 0b11;
}

uint8_t Header::get_team(){
    return head & 0b1;
}

void Header::decode(uint16_t * code, uint8_t * id, uint8_t * team){
    *code = get_code();
    *id = get_id();
    *team = get_team();
}

void Header::set_code(uint16_t code){
    head = (code << 3) | (head & 0b111);
}

void Header::set_id(uint8_t id){
    head = ((head >> 3) << 3) | (id << 1) | (head & 0b1);
}

void Header::set_team(uint8_t team){
    head = ((head >> 1) << 1) | team;
}

char * Header::serialize(ssize_t * packet_size){
    char * serialized = new char[2];
    memcpy(serialized, &head, 2);
    *packet_size = 2;  
    return serialized;
}

int Header::send_header(const int sock_fd){

  ssize_t packet_size;
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

  print(INFO, "sent request packet to server");
  return 0;
}

int Header::recv_header(const int sock_fd){
  char buf[2];
  memset(buf, 0, sizeof(char)*2);
  ssize_t byte_recved = 0;
  ssize_t total = 0;
  while(total < 2){
    byte_recved = recv(sock_fd, buf+byte_recved, 2-byte_recved, 0);
    if(byte_recved == -1){
      print(ERROR, "Error reciving packet");
      return -1;
    }
    total+=byte_recved;
  }
  memcpy(&head, buf, 2);
  print(INFO, "Recived header: " + to_string());
  return 0;
}

string Header::to_string(){
    return "Header:\n\tcode: " + std::to_string(get_code()) + " id: " + std::to_string(get_id()) + " team: " + std::to_string(get_team());
}
