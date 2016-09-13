#include "tcpsocket.hpp"
#include <unistd.h>
#include <iostream>
#include <memory>

int main(int argc, char *argv[])
{
  if(argc < 4) return -1;
  using namespace sssocket;
  using std::cout;
  using std::endl;
  using std::shared_ptr;
  using std::string;
  TcpSocket socket;
  socket.connect(argv[1], argv[2]);
  cout << *socket.readLine() << endl;
  socket.sendString(string(argv[3]));
  auto s = socket.readLine();
  while (*s != "OK" )
    {
      cout << *s << endl;
      s = socket.readLine();
    }
  cout << *s << endl;
  return 0;
}
