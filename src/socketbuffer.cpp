#include "socketbuffer.hpp"
#include "tcpsocket.hpp"
#include <cstring>
#include <unistd.h>

using namespace sssocket;

// from Nicolai M Josuttis' Book "The C++ Standard Library" pg. 841

SocketBuffer::SocketBuffer(int socket_file_descriptor)
  :file_descriptor(socket_file_descriptor)
{
  setg(read_buffer+put_back_size,
       read_buffer+put_back_size,
       read_buffer+put_back_size);
}

void
SocketBuffer::setSocketFileDescriptor(int socket_file_descriptor)
{
  file_descriptor = socket_file_descriptor;
}

SocketBuffer::int_type
SocketBuffer::underflow()
{
  if(gptr() < egptr())
    {
      return traits_type::to_int_type(*gptr());
    }

  int current_put_back_size = gptr() - eback();
  if (current_put_back_size > put_back_size) current_put_back_size = put_back_size;

  std::memmove(read_buffer + put_back_size - current_put_back_size,
               gptr() - current_put_back_size,
               current_put_back_size);

  int bytes_read = ::read(file_descriptor, eback(), read_buffer_size - put_back_size);

  if (bytes_read < 0) return EOF;

  setg(read_buffer + put_back_size - current_put_back_size,
       read_buffer + put_back_size,
       read_buffer + put_back_size + bytes_read);

  return traits_type::to_int_type(*gptr());

}
