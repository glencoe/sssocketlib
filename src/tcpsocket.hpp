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
#include "C/socket.h"
#include "socketbuffer.hpp"

namespace sssocket
{
  using std::string;

  class TcpSocket
  {

  public:
    TcpSocket();
    TcpSocket(const string& host_name, const string& port);
    ~TcpSocket();
    void connect(const string& host_name, const string& port_number);
    void connect(const char* host_name, const char* port);
    void sendString(const std::string& message) const;
    std::unique_ptr<std::string> readLine();
    int send(const char *buffer, int buffer_len, int flags = 0) const;
    int receive(char *buffer, int buffer_len, int flags = 0) const;
    int read(char *buffer, int buffer_len) const;

  private:
    int file_descriptor;
    string host_name;
    string port;
    bool isConnected;
    std::unique_ptr<SocketBuffer> read_buffer;
  };

}

#endif /* end of include guard: TCPSOCKET_HPP */
