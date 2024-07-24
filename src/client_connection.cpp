#include "client_connection.hpp"

sockaddr_in connect_to_server(const int port, const std::string adress, int * tcp_server_sock){
  *tcp_server_sock = socket(AF_INET, SOCK_STREAM, 0);
  if (*tcp_server_sock < 0) {
    print(ERROR, "Socket cannot be created!");
    exit(EXIT_FAILURE);
  }
  print(INFO, "Socket created.");

  sockaddr_in server_addr;
  memset((char*)&server_addr, 0, sizeof(server_addr));
  server_addr.sin_family = AF_INET;
  server_addr.sin_port = htons(port);
  inet_pton(AF_INET, adress.c_str(), &server_addr.sin_addr);
  

  if (connect(*tcp_server_sock, (sockaddr*)&server_addr, sizeof(server_addr)) < 0) {
    print(ERROR, "Connection failed!");
    exit(EXIT_FAILURE);
  }
  print(INFO, "Connected to server.");
  return server_addr;

}

struct sockaddr_in6 create_udp_client_sockaddr(const char* ipv6,int port){
    struct sockaddr_in6 udp_server_addr;
    memset(&udp_server_addr, 0, sizeof(udp_server_addr));
    udp_server_addr.sin6_family = AF_INET6; // IPv6
    inet_pton(AF_INET6, ipv6, &udp_server_addr.sin6_addr);
    udp_server_addr.sin6_port = htons(port);
    return udp_server_addr;

}

int create_mcast_sock(){
  int mcast_client_sock;
  if((mcast_client_sock = socket(AF_INET6, SOCK_DGRAM, 0))<0){
    close(mcast_client_sock);
    print(ERROR, "Error creating socket");
    exit(EXIT_FAILURE);
  }
  //inscription sock option for reuse
  int ok = 1;
  if(setsockopt(mcast_client_sock, SOL_SOCKET, SO_REUSEADDR, &ok, sizeof(ok)) < 0) {
    print(ERROR, "Error setting socket options");
    close(mcast_client_sock);
    exit(EXIT_FAILURE);
  }
  return mcast_client_sock;
}

struct sockaddr_in6 create_mcast_sockaddr(int mcast_sock,int mcast_port){
  struct sockaddr_in6 mcast_sockaddr;
  memset(&mcast_sockaddr, 0, sizeof(mcast_sockaddr));
  mcast_sockaddr.sin6_family = AF_INET6;
  mcast_sockaddr.sin6_addr = in6addr_any;
  mcast_sockaddr.sin6_port = htons(mcast_port);

  //bind to multicast
  if(bind(mcast_sock, (struct sockaddr*) &mcast_sockaddr, sizeof(mcast_sockaddr))) {
      print(ERROR, "Error binding to multicast");
      close(mcast_sock);
      exit(EXIT_FAILURE);
  }

  return mcast_sockaddr;

}

void inscribe_to_mcast(int mcast_client_sock, char * ip){
  //multicast protocol
  int ifindex = if_nametoindex ("enp1s0");
  if(ifindex == 0)
    print(ERROR, "prototocl err:");

  // insciption to multicast
  struct ipv6_mreq group;
  inet_pton (AF_INET6, ip, &group.ipv6mr_multiaddr.s6_addr);
  group.ipv6mr_interface = ifindex;
  if(setsockopt(mcast_client_sock, IPPROTO_IPV6, IPV6_JOIN_GROUP, &group, sizeof group) < 0) {
      print(ERROR, "inscription err:");
      close(mcast_client_sock);
      exit(EXIT_FAILURE);
  }
}