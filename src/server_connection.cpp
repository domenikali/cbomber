#include "server_connection.hpp"

std::stack<int> solo_queue;
std::stack<int> team_queue;

std::mutex solo_queue_mutex;
std::mutex team_queue_mutex;

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
  
  switch (mode)
  {
  case 2:
    solo_queue_mutex.lock();
    for (int i =0;i<LOBBY_SIZE;i++){
      Header::success_header().send_header(solo_queue.top());
      solo_queue.pop();
    }
    solo_queue_mutex.unlock();
    break;
  case 3:
    team_queue_mutex.lock();
    for (int i =0;i<LOBBY_SIZE;i++){
      Header::success_header().send_header(team_queue.top());
      team_queue.pop();
    }
    team_queue_mutex.unlock();
    break;
  
  default:
    print(ERROR,"Invalid mode");
    exit(EXIT_FAILURE);
    break;
  }
}

