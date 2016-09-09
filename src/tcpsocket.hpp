#ifndef TCPSOCKET_HPP
#define TCPSOCKET_HPP

/* POSIX header for linux */
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>

/* cpp headers */
#include <string>
#include <memory>

/* our headers */
#include "socketbuffer.hpp"

namespace sssocket
{

  class TcpSocket
  {

  sockaddr_in *getHostByNameIpv4(std::string& host_name, uint16_t port_number = 0);
  sockaddr_in *copyPosixSocketAddressIpv4(const sockaddr *address);

  using buffer_type = SocketBuffer;
  using address_type = std::shared_ptr<sockaddr_in>;

  public:
    TcpSocket();
    ~TcpSocket();

  private:
    buffer_type buffer;
    int file_descriptor;
  };



}

#endif /* end of include guard: TCPSOCKET_HPP */
