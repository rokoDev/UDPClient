//
//  SocketAddress.cpp
//  UDPServer
//
//  Created by roko on 15/05/2019.
//
#include "SocketAddress.h"

#include <cstring>

namespace net
{
SocketAddress::SocketAddress(uint32_t ipV4Address, uint16_t port)
{
    GetAsSockAddrIn()->sin_family = AF_INET;
    GetAsSockAddrIn()->sin_addr.s_addr = htonl(ipV4Address);
    GetAsSockAddrIn()->sin_port = htons(port);
}

SocketAddress::SocketAddress(const sockaddr &sockAddr)
{
    memcpy(&_sockAddr, &sockAddr, sizeof(sockaddr));
}

std::size_t SocketAddress::getSize() const noexcept { return sizeof(sockaddr); }

sockaddr_in *SocketAddress::GetAsSockAddrIn() noexcept
{
    return reinterpret_cast<sockaddr_in *>(&_sockAddr);
}
}  // namespace net
