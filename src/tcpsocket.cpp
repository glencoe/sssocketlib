#include "tcpsocket.hpp"
#include "socketexception.hpp"
#include "socketbuffer.hpp"
#include <cstring>
#include <iostream>
#include <istream>
#include <unistd.h>
#include <stropts.h>

using namespace sssocket;

TcpSocket::TcpSocket()
  : file_descriptor(-1)
  , host_name("")
  , isConnected(false)
  , read_buffer(nullptr)
{
  read_buffer = std::unique_ptr<SocketBuffer>(new SocketBuffer(file_descriptor));
}

TcpSocket::TcpSocket(const std::string& host_name, const std::string& port)
  :TcpSocket()
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
  lock_guard<mutex> lock(socket_mutex);
  if (file_descriptor > 0)
    {
      close(file_descriptor);
      file_descriptor = -1;
    }
  file_descriptor = create_and_connect_stream_socket(host_name, port, INET_PROTOCOL_BOTH, 0);

  if(file_descriptor == -1)
    {
      SocketException exception("could not create socket");
      throw exception;
    }
  isConnected = true;
  read_buffer->setSocketFileDescriptor(file_descriptor);
}

int
TcpSocket::send(const char *buffer, int buffer_len, int flags) const
{
  lock_guard<mutex> lock(socket_mutex);
  return ::send(file_descriptor, buffer, buffer_len, flags);
}

int
TcpSocket::receive(char *buffer, int buffer_len, int flags) const
{
  lock_guard<mutex> lock(socket_mutex);
  return ::recv(file_descriptor, buffer, buffer_len, flags);
}

int
TcpSocket::read(char* buffer, int buffer_len) const
{
  lock_guard<mutex> lock(socket_mutex);
  return ::read(file_descriptor, buffer, buffer_len);
}

void
TcpSocket::sendString(const std::string& message) const
{
  lock_guard<mutex> lock(socket_mutex);
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
}

void
TcpSocket::writeString(const std::string& message) const
{
  sendString(message);
}

void
TcpSocket::writeLine(const std::string& message) const
{
  writeString(message);
  writeString("\n");
}

std::unique_ptr<std::string>
TcpSocket::readLine()
{
  lock_guard<mutex> lock(socket_mutex);
  std::istream stream(read_buffer.get());
  std::string * message = new std::string();
  char c = -1;
  while(true)
    {
      stream.get(c);
      if(c== '\n') break;
      message->push_back(c);
    }
  return std::unique_ptr<std::string>(message);

}
