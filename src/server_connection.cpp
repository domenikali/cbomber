#include "server_connection.hpp"

std::queue<int> solo_queue;
std::queue<int> team_queue;

std::mutex solo_queue_mutex;
std::mutex team_queue_mutex;

int base_udp_port = 8080;
int base_mcast_port = 9080;

std::mutex base_udp_port_mutex;
std::mutex base_mcast_port_mutex;

int create_server_socket(const int port){

  //init socket
  int tcp_server_sock = socket(AF_INET, SOCK_STREAM, 0);
  if (tcp_server_sock < 0) {
    print(ERROR,"Socket cannot be created.");
    exit(EXIT_FAILURE);
  }
  print(INFO,"Socket is created.");

  const int enable = 1;
  if (setsockopt(tcp_server_sock, SOL_SOCKET, SO_REUSEADDR, &enable, sizeof(int)) < 0)
    print(ERROR,"setsockopt(SO_REUSEADDR) failed");

  sockaddr_in server_addr;
  server_addr.sin_family = AF_INET;
  server_addr.sin_port = htons(port);
  server_addr.sin_addr.s_addr = INADDR_ANY;
  print(INFO,"Server address is created.");
  
  if (bind(tcp_server_sock, (sockaddr *)&server_addr, sizeof(server_addr)) < 0) {
    print(ERROR,"Socket cannot be binded.");
    exit(EXIT_FAILURE);
  }
  print(INFO,"Socket is binded.");

  if (listen(tcp_server_sock, 0) < 0) {
    print(ERROR,"Socket cannot listen.");
    exit(EXIT_FAILURE);
  }
  print(INFO,"Socket is listening.");
  return tcp_server_sock;
}

sockaddr_in accept_client(const int tcp_server_sock, int *sock_client){
  sockaddr_in client_addr;
  socklen_t client_addr_size = sizeof(client_addr); 
  
  if ((*sock_client = accept(tcp_server_sock, (sockaddr*)&client_addr, &client_addr_size)) < 0) {
    print(ERROR,"Connections cannot be accepted for a reason.");
    exit(EXIT_FAILURE);
  }

  print(INFO,"A connection is accepted now.");
  return client_addr;
}

void queue_client(const int client_sock){
  int mode = Header::recv_header(client_sock).get_code();
  
  switch(mode){
    case 2://single player
      solo_queue_mutex.lock();
      solo_queue.push(client_sock);
      if(solo_queue.size()>=4){
        std::thread t(lobby, mode);
        t.detach();
      }
      solo_queue_mutex.unlock();
      break;

    case 3://teams
      team_queue_mutex.lock();
      team_queue.push(client_sock);
      if(team_queue.size()>=4){
        std::thread t(lobby, mode);
        t.detach();
      }
      team_queue_mutex.unlock();
      break;

    default:
      print(ERROR,"Invalid header received");
      Header::error_header().send_header(client_sock);
      return;
      break;
  }

  Header header_ok = Header(0,0,0);
  header_ok.send_header(client_sock);
  
}

void lobby(const int mode){

  Match_info match = init_match();
  Header header(0,0,0);

  int mdiff_server_sock;
  mdiff_server_sock = socket(AF_INET6, SOCK_DGRAM, 0);
        
        
  struct sockaddr_in6 gradr;
  memset(&gradr, 0, sizeof(gradr));
  gradr.sin6_family = AF_INET6;
  inet_pton(AF_INET6, match.get_mcast_addr_str(), &gradr.sin6_addr);
  gradr.sin6_port = htons(match.get_mcast_port() );


  int ifindex = if_nametoindex ("enp1s0");
  if(ifindex == 0)
    perror("if_nametoindex");

  gradr.sin6_scope_id = ifindex;
  print(INFO,"mdiff created");


  Player players[LOBBY_SIZE];
  int players_count=0;
  while(players_count<LOBBY_SIZE){
    switch (mode){
      case 2:
        solo_queue_mutex.lock();
        players[players_count].tcp_socket=solo_queue.front();
        players[players_count].id = players_count;
        solo_queue.pop();
        solo_queue_mutex.unlock();

        header.set_id(players_count); 
        match.set_header(header);
        match.send_match_info(players[players_count].tcp_socket);

        players_count++;
        break;
      case 3:
        team_queue_mutex.lock();
        players[players_count].tcp_socket=team_queue.front();
        players[players_count].id = players_count;
        team_queue.pop();
        team_queue_mutex.unlock();

        header.set_id(players_count); 
        match.set_header(header);
        match.send_match_info(players[players_count].tcp_socket);
        players_count++;
        break;
      
      default:
        print(ERROR,"Invalid mode");
        exit(EXIT_FAILURE);
        break;
    }
  }
  // multicast test
  sleep(1);
  Game grid = Game();
  //print(INFO,"grid created "+grid.to_string());
  grid.printGrid();
  uint8_t grid_dimensions[2] = {grid.getGridHeight(), grid.getGridWidth()};
    
  

  for(int i=0;i<4;i++){
    grid.send_tcp_grid(players[i].tcp_socket);
  } 
  print(INFO,"grid info sent");

  
  //send game grid to tcp sockets
  
  
}

Match_info init_match(){
  char * mcast_addr = new_mdiff_adress();
  base_mcast_port_mutex.lock();
  int mcast_port = base_mcast_port++;
  base_mcast_port_mutex.unlock();
  base_udp_port_mutex.lock();
  int udp_port = base_udp_port++;
  base_udp_port_mutex.unlock();
  return Match_info(Header::success_header(), udp_port, mcast_port, mcast_addr);

}


char * new_mdiff_adress() {

    char* base=strdup("ff12:0000:0000:0000:0000:0000:0000:0000");
    if (base==NULL)
    {
        perror("Memory allocation failled");
        pthread_exit((void*)EXIT_FAILURE);
    }
    
    // Generate random hexadecimal characters for the existing address
    for (int i = 5; i < 39; i += 4) {
        for (int j = 0; j < 4; j++) {
            int r = rand() % 16; // Generate random number between 0 and 15 (little bug, changed to 0-9 for the moment)
            char hex_digit = (r < 10) ? (char)(r + '0') : (char)(r - 10 + 'a'); // Convert to hexadecimal digit
            //printf("%c\n", hex_digit);
            base[i + j] = hex_digit;
        }
        if (i != 35)
            i++;
    }

    return base;
}



