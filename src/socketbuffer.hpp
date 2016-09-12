#ifndef SOCKETBUFFER_HPP
#define SOCKETBUFFER_HPP

#include <vector>

namespace sssocket
{
  using std::vector;

  class SocketBuffer
  {
  public:
    SocketBuffer(int size);
    char * data();
    int size() const;

  private:
    vector<char> buffer;

  };

}

#endif /* end of include guard: SOCKETBUFFER_HPP */
