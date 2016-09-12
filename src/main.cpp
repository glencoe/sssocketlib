#include "tcpsocket.hpp"
#include <iostream>

int main(int argc, char *argv[])
{
  if(argc < 4) return -1;
  using namespace sssocket;
  using std::cout;
  using std::endl;
  TcpSocket socket;
  socket.connect(argv[1], argv[2]);
  cout << *socket.readString();
  socket.sendString(std::string(argv[3]).append("\n"));
  cout << *socket.readString();
  return 0;
}
