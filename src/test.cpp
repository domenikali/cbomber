#include <iostream>
#include <ctime>
#include <cstdlib>
#include <cstring>

#include <arpa/inet.h>


using namespace std;

int main (int args, char ** argv){
  string ip = "AF12::1";  
  cout << ip << endl;
  
  uint8_t ip6[16];
  memset(ip6, 0, 16); 
  inet_pton(AF_INET6, ip.c_str(), &ip6);
  
  cout << ip << endl;

  for(int i = 0 ; i < 16; i++){
    cout << (int)ip6[i] << " ";
  }
  cout << endl;
  char * ip_str = new char[16];
  inet_ntop(AF_INET6, ip6, ip_str, 16);
  cout << ip_str << endl;
  return 0;
}