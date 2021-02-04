#include <fmt/format.h>
#include <ndt/address.h>
#include <ndt/socket.h>
#include <ndt/udp.h>
#include <ndt/utils.h>
#include <ndt/version_info.h>

#include <iostream>

#include "client/version_info.h"

#define SERVER "127.0.0.1"
#define BUFLEN 512  // Max length of buffer
#define PORT 8888   // The port on which to send data

int main(void)
{
    try
    {
        fmt::print("{}", client::version_info());
        fmt::print("{}", ndt::version_info());
        std::string userMsg;
        ndt::UDP::Socket s = ndt::UDP::Socket(ndt::UDP::V4(), 111);
        ndt::Address sender;
        const std::size_t kBufSize = 512;
        char buf[kBufSize] = {0};
        while (1)
        {
            fmt::print("\nEnter message: ");
            std::getline(std::cin, userMsg);
            fmt::print("your msg:{} has {} byte of size\n", userMsg,
                       userMsg.size());
            if (userMsg == std::string("q"))
            {
                s.close();
                break;
            }
            s.sendTo(ndt::Address(ndt::kIPv4Loopback, PORT), userMsg.data(),
                     userMsg.size());
            const auto bytesRecieved = s.recvFrom(buf, kBufSize, sender);
            buf[bytesRecieved] = '\0';
            fmt::print("Recieved from: {}\n", sender.port());
            fmt::print("Content: {}", (char *)(buf));
        }
    }
    catch (const ndt::exception::RuntimeError &re)
    {
        std::cout << re;
    }
    catch (const ndt::exception::LogicError &le)
    {
        std::cout << le;
    }
    catch (std::exception &e)
    {
        fmt::print("Error: {}\n", e.what());
    }
    catch (...)
    {
        fmt::print("unknown error");
    }

    return 0;
}
