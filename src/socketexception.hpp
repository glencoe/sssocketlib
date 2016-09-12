#ifndef SOCKETEXCEPTION_H
#define SOCKETEXCEPTION_H

#include <exception>
#include <string>

namespace sssocket
{

// Base class for exceptions in this library
  class SocketException : public std::exception
  {
  public:
    SocketException(const std::string& message) :message(message){};
    const char* what() const noexcept {return message.c_str();};
  private:
    std::string message;
  };

}

#endif /* SOCKETEXCEPTION_H */
