#include "socketbuffer.hpp"

using namespace sssocket;

SocketBuffer::SocketBuffer(int size)
{
  
}

char*
SocketBuffer::data()
{
  return buffer.data();
}

int
SocketBuffer::size() const
{
  return buffer.size();
}
