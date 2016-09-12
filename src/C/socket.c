#include <string.h>
#include <stdio.h>
#include <unistd.h>

#include "socket.h"

int
prepare_addressinfo_hint(struct addrinfo* hint, internet_protocol protocol_family, int flags)
{
  memset(hint, 0, sizeof(struct addrinfo));

  switch (protocol_family)
    {
    case INET_PROTOCOL_IPV4:
      hint->ai_family = AF_INET;
      break;

    case INET_PROTOCOL_IPV6:
      hint->ai_family = AF_INET6;
      break;

    case INET_PROTOCOL_BOTH:
      hint->ai_family = AF_UNSPEC;
      break;

    default:
      fprintf(stderr, "no valid internet protocol specified");
      return -1;
    }

  hint->ai_socktype = SOCK_STREAM;
  hint->ai_flags = flags;
  hint->ai_protocol = 0; // protocol is tcp
  
  return 0;
}


int
create_and_connect_stream_socket(const char* host_name, const char* port, internet_protocol protocol_family, int flags)
{
  int error_code = 0;
  int socket_file_descriptor = -1;
  struct addrinfo hint;
  error_code = prepare_addressinfo_hint(&hint, protocol_family, flags);
  if(error_code < 0) return -1;

  struct addrinfo *list_of_addresses_ptr;
  struct addrinfo *current_address_ptr;

  error_code = getaddrinfo(host_name,
                           port,
                           &hint,
                           &list_of_addresses_ptr);

  if(error_code < 0)
    {
      fprintf(stderr, "could not resolve address: %s", gai_strerror(error_code));
      freeaddrinfo(list_of_addresses_ptr);
      return -1;
    }

  for(current_address_ptr = list_of_addresses_ptr; current_address_ptr != NULL; current_address_ptr = current_address_ptr->ai_next)
    {
      socket_file_descriptor = socket(current_address_ptr->ai_family,
                                      current_address_ptr->ai_socktype,
                                      current_address_ptr->ai_protocol);
      if(socket_file_descriptor < 0) continue;

      error_code = connect(socket_file_descriptor,
                           current_address_ptr->ai_addr,
                           current_address_ptr->ai_addrlen);
      if(error_code == 0) break;

      close(socket_file_descriptor); // connect was unsuccessful
    }

  if(current_address_ptr == NULL)
    {
      fprintf(stderr, "could not connect to %s : %s", host_name, port);
      return -1;
    }

  freeaddrinfo(list_of_addresses_ptr);
  return socket_file_descriptor;
}
