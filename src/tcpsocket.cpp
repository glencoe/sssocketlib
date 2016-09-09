#include "tcpsocket.hpp"
#include <cstring>

using namespace sssocket;

sockaddr_in *
getHostAddressByNameIpv4(std::string& host_name, uint16_t port_number = 0)
{
  sockaddr_in * host_address = nullptr;
  addrinfo * address_info_list = nullptr;

  std::string port_number_string = std::to_string(port_number);

  addrinfo pattern_for_finding_host;
  pattern_for_finding_host.ai_family = AF_INET; /* set to ipv4 */
  pattern_for_finding_host.ai_socktype = SOCK_STREAM; /* set to stream opposed to SOCK_DGRAM */
  pattern_for_finding_host.ai_flags = 0;

  int error_code = 0;

  if (port_number == 0) {
    error_code = getaddrinfo(host_name.c_str(),
                              NULL,
                              &pattern_for_finding_host,
                              &address_info_list);
  } else {
    error_code = getaddrinfo(host_name.c_str(),
                              port_number_string.c_str(),
                              &pattern_for_finding_host,
                              &address_info_list);
  }

  if (error_code == 0) {
    host_address = copyPosixSocketAddressIpv4(address_info_list->ai_addr);
  }

  freeaddrinfo(address_info_list);

  return host_address;
}

sockaddr_in *
copyPosixSocketAddressIpv4(const sockaddr * address)
{
  sockaddr_in *result = (sockaddr_in*) malloc(sizeof(sockaddr_in));
  memcpy(result, address, sizeof(sockaddr_in));
  return result;
}
