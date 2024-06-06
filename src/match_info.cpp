#include "match_info.hpp"

Match_info::Match_info(Header header, uint16_t udp_port, uint16_t mcast_port, std::string mcast_addr){
  this->header = header;
  this->udp_port = htons(udp_port);
  this->mcast_port = htons(mcast_port);
  inet_pton(AF_INET6, mcast_addr.c_str(), this->mcast_addr);
}

Match_info::Match_info(const char * serialized_match_info){
  int offset = 0;
  memcpy(&header, serialized_match_info, 2);
  offset += 2;
  memcpy(&udp_port, serialized_match_info + offset, 2);
  offset += 2;
  memcpy(&mcast_port, serialized_match_info + offset, 2);
  offset += 2;
  memcpy(mcast_addr, serialized_match_info + offset, 16);
}

char * Match_info::get_mcast_addr_str(){
  char * addr = new char[INET6_ADDRSTRLEN];
  inet_ntop(AF_INET6, mcast_addr, addr, 16);
  return addr;
}

char * Match_info::serialize(ssize_t * packet_size){
  char * serialized = new char[22];
  int offset = 0;
  memcpy(serialized, &header, 2);
  offset += 2;
  memcpy(serialized + offset, &udp_port, 2);
  offset += 2;
  memcpy(serialized + offset, &mcast_port, 2);
  offset += 2;
  memcpy(serialized + offset, mcast_addr, 16);
  *packet_size = 22;
  return serialized;
}

int Match_info::send_match_info(const int sock_fd){
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
  print(INFO, "Match info sent successfully");
  return 0;
}

Match_info Match_info::recv_match_info(const int sock_fd){
  ssize_t packet_size = 22;
  char * serialized_packet = new char[22];
  ssize_t total = 0, bytes_recv=0;
  while(total < packet_size){
    bytes_recv = recv(sock_fd, serialized_packet + total, packet_size - total, 0);
    if(bytes_recv == -1){
      print(ERROR, "Error receiving packet");
      return Match_info(Header::error_header(), 0, 0, {0});
    }
    total += bytes_recv;
  }
  Match_info match_info(serialized_packet);
  delete[] serialized_packet;
  print(INFO, "Match info received successfully");
  return match_info;
}

std::string Match_info::to_string(){
  return header.to_string() + " port udp: " + std::to_string(ntohs(udp_port)) + " port mcast: " + std::to_string(ntohs(mcast_port)) + " ip mcast: " + std::string(get_mcast_addr_str());
}
