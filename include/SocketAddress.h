//
//  SocketAddress.h
//  UDPServer
//
//  Created by roko on 15/05/2019.
//

#ifndef SocketAddress_h
#define SocketAddress_h

#include <cstddef>
#include <cstdint>

#include "CommonInclude.h"

namespace net
{
class SocketAddress
{
   public:
    SocketAddress(uint32_t ipV4Address, uint16_t port);
    explicit SocketAddress(const sockaddr& inSockAddr);
    inline std::size_t getSize() const noexcept;

   private:
    inline sockaddr_in* GetAsSockAddrIn() noexcept;
    sockaddr _sockAddr;
};
}  // namespace net

#endif /* SocketAddress_h */
