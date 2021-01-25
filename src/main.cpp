#include <fmt/format.h>
#include <ndt/GitInfo.h>
#include <ndt/Version.h>
#include <ndt/address.h>
#include <ndt/socket.h>
#include <ndt/udp.h>
#include <ndt/utils.h>

#include <iostream>

#include "client/GitInfo.h"
#include "client/Version.h"

#define SERVER "127.0.0.1"
#define BUFLEN 512  // Max length of buffer
#define PORT 8888   // The port on which to send data

void printVersionInfo()
{
    fmt::print("Version: {}\n", client::Version::str());
    fmt::print("branch: {}\n", client::GitInfo::branch());
    fmt::print("SHA1: {}\n", client::GitInfo::SHA1());
    const std::string isDirty =
        client::GitInfo::isDirty() ? std::string("true") : std::string("false");
    fmt::print("IS_DIRTY: {}\n", isDirty);
}

int main(void)
{
    try
    {
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
