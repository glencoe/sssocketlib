#ifndef SOCKETBUFFER_HPP
#define SOCKETBUFFER_HPP

#include <streambuf>
#include <memory>


namespace sssocket
{

  class SocketBuffer : public std::streambuf
  {
  public:
    SocketBuffer(int socket_file_descriptor);
    void setSocketFileDescriptor(int socket_file_descriptor);

  protected:
    virtual int_type underflow();

  private:
    static const int read_buffer_size = 1024;
    static const int put_back_size = 1;
    char read_buffer[read_buffer_size];
    int file_descriptor;


  };

}

#endif /* end of include guard: SOCKETBUFFER_HPP */
