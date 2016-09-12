#include "tcpsocket.hpp"
#include "socketexception.hpp"
#include <cstring>
#include <sstream>
#include <iostream>
#include <iterator>
#include <vector>
#include <unistd.h>

using namespace sssocket;

TcpSocket::TcpSocket()
  : file_descriptor(-1)
  , host_name("")
  , isConnected(false)
{
}

TcpSocket::TcpSocket(const std::string& host_name, const std::string& port)
{
  connect(host_name, port);
}

TcpSocket::~TcpSocket()
{
  close(file_descriptor);
}

void
TcpSocket::connect(const std::string& host_name, const std::string& port)
{
  this->TcpSocket::connect(host_name.c_str(), port.c_str());
}

void
TcpSocket::connect(const char* host_name, const char* port)
{
  file_descriptor = create_and_connect_stream_socket(host_name, port, INET_PROTOCOL_BOTH, 0);

  if(file_descriptor == -1)
    {
      SocketException exception("could not create socket");
      throw exception;
    }
  isConnected = true;
}

int
TcpSocket::send(void *buffer, int buffer_len, int flags) const
{
  return ::send(file_descriptor, buffer, buffer_len, flags);
}

int
TcpSocket::receive(void *buffer, int buffer_len, int flags) const
{
  return ::recv(file_descriptor, buffer, buffer_len, flags);
}

void
TcpSocket::sendString(const std::string& message) const
{
  int data_size = message.length() +1;
  int amount_of_data_written = 0;
  int write_chunk_size = 4096;
  int amount_of_data_to_write = 0;
  const char *data_ptr = message.c_str();
  const char *cur_pos = data_ptr;

  while(data_size > 0)
    {
      if(data_size > write_chunk_size) amount_of_data_to_write = write_chunk_size;
      else amount_of_data_to_write = data_size;
      amount_of_data_written = write(file_descriptor, cur_pos, amount_of_data_to_write);
      data_size -= amount_of_data_written;
      cur_pos += amount_of_data_written;
    }
  std::cout << "string successfull sent" << std::endl;
}

std::unique_ptr<std::string>
TcpSocket::readString() const
{
  std::string* message = new std::string();
  int buffer_size = 512;
  char buffer[buffer_size];
  memset(buffer, 0, buffer_size);
  int amount_read_data = buffer_size;
  while(amount_read_data > 0)
    {
      amount_read_data = ::read(file_descriptor, buffer, buffer_size);
      if(amount_read_data < 0) break;
      message->append(buffer,amount_read_data);
      if (amount_read_data < buffer_size && buffer[amount_read_data-1] == '\n') break;
    }
  return std::unique_ptr<std::string>(message);
}
