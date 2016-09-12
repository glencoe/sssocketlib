#ifndef TCPSOCKET_HPP
#define TCPSOCKET_HPP

/* POSIX header for linux */
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>

/* cpp headers */
#include <string>
#include <memory>
#include <vector>

/* our headers */
#include "socketbuffer.hpp"
#include "C/socket.h"

namespace sssocket
{
  using std::string;

  class TcpSocket
  {

    using address_type = std::shared_ptr<sockaddr_in>;

  public:
    TcpSocket();
    TcpSocket(const string& host_name, const string& port);
    ~TcpSocket();
    void connect(const string& host_name, const string& port_number);
    void connect(const char* host_name, const char* port);
    void sendString(const std::string& message) const;
    std::unique_ptr<std::string> readString() const;
    int send(SocketBuffer buffer, int flags = 0) const;
    int receive(SocketBuffer buffer, int flags = 0) const;

  private:
    int file_descriptor;
    string host_name;
    string port;
    bool isConnected;
  };

  /* helper functions */
  sockaddr_in *getHostAddressByNameIpv4(const char* host_name, const char* port);
  sockaddr_in *copyPosixSocketAddressIpv4(const sockaddr *address);
}

#endif /* end of include guard: TCPSOCKET_HPP */
