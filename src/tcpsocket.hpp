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
#include <mutex>

/* our headers */
#include "C/socket.h"
#include "socketbuffer.hpp"

namespace sssocket
{
  using std::string;
  using std::unique_ptr;
  using std::mutex;
  using std::lock_guard;

  class TcpSocket
  {

  public:
    TcpSocket();
    TcpSocket(const string& host_name, const string& port);
    ~TcpSocket();
    void connect(const string& host_name, const string& port_number);
    void connect(const char* host_name, const char* port);
    void sendString(const string& message) const;
    void writeString(const string& message) const;
    unique_ptr<string> readLine();
    void writeLine(const string& message) const;
    int send(const char *buffer, int buffer_len, int flags = 0) const;
    int receive(char *buffer, int buffer_len, int flags = 0) const;
    int read(char *buffer, int buffer_len) const;

  private:
    int file_descriptor;
    string host_name;
    string port;
    bool isConnected;
    std::unique_ptr<SocketBuffer> read_buffer;
    mutable mutex socket_mutex;

  };
}

#endif /* end of include guard: TCPSOCKET_HPP */
