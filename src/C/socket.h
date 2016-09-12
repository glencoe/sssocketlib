#ifndef CSOCKETS_H
#define CSOCKETS_H

#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef enum internet_protocol {
  INET_PROTOCOL_IPV4 = 1,
  INET_PROTOCOL_IPV6 = 2,
  INET_PROTOCOL_BOTH = 3
} internet_protocol;

extern int create_and_connect_stream_socket(const char* host_name, const char* port, internet_protocol protocol, int flags);

#ifdef __cplusplus
}
#endif

#endif
