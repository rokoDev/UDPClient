#include <fmt/format.h>
#include <ndt/core.h>

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
        ndt::Context<ndt::System> ctx;
        ndt::UDP::Socket s = ndt::UDP::Socket(ctx, ndt::UDP::V4(), 111);
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
            s.sendTo(ndt::Address(ndt::kIPv4Loopback, PORT),
                     ndt::CBuffer(userMsg.data(), userMsg.size()));
            ndt::Buffer recvBuf(buf);
            const auto bytesRecieved = s.recvFrom(recvBuf, sender);
            buf[bytesRecieved] = '\0';

            // print details of the the data received
            fmt::print("Recieved from: {}\n", sender.port());
            fmt::print("\n{} bytes received: {}", recvBuf.size(),
                       fmt::format("{:.{}}", buf, recvBuf.size()));
        }
    }
    catch (const ndt::Error &e)
    {
        fmt::print("ndt::Error >> code: {}. reason: {}\n", e.code().value(),
                   e.what());
    }
    catch (std::exception &e)
    {
        fmt::print("Error >> reason: {}\n", e.what());
    }
    catch (...)
    {
        fmt::print("unknown error");
    }

    return 0;
}
