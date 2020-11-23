#include <fmt/core.h>

#include <iostream>

#include "Address.h"
#include "GitInfo.h"
#include "NetException.h"
#include "Socket.h"
#include "UDP.h"
#include "Version.h"

#define SERVER "127.0.0.1"
#define BUFLEN 512  // Max length of buffer
#define PORT 8888   // The port on which to send data

void die(std::string s)
{
    perror(s.c_str());
    exit(1);
}

void printVersionInfo()
{
    fmt::print("Version: {}\n", UDPClient::Version::str());
    fmt::print("branch: {}\n", UDPClient::GitInfo::branch());
    fmt::print("SHA1: {}\n", UDPClient::GitInfo::SHA1());
    const std::string isDirty = UDPClient::GitInfo::isDirty()
                                    ? std::string("true")
                                    : std::string("false");
    fmt::print("IS_DIRTY: {}\n", isDirty);
}

int main(void)
{
    // printVersionInfo();
    //    addrinfo hint;
    //    memset(&hint, 0, sizeof(hint));
    //    hint.ai_family = AF_UNSPEC;//AF_INET6;//AF_INET;//AF_UNSPEC;
    //
    //    net::SocketAddress endPoint;
    //    endPoint.setPort(555);
    //
    //    addrinfo *ai;
    //    const auto res = getaddrinfo("localhost", nullptr, &hint, &ai);
    //    if (res != 0) {
    //        fmt::print("Error({}): {}\n", errno, std::strerror(errno));
    //    }
    //    else {
    //        const size_t bufSize = 64;
    //        char buf[bufSize] = {0};
    //        for (addrinfo *cur_ai = ai; cur_ai != nullptr; cur_ai =
    //        cur_ai->ai_next) {
    //            std::string familyStr;
    //            switch (cur_ai->ai_family) {
    //                case AF_INET:
    //                {
    //                    sockaddr_in *saddr = (sockaddr_in*)cur_ai->ai_addr;
    //                    inet_ntop(cur_ai->ai_family, &(saddr->sin_addr), buf,
    //                    bufSize); familyStr = std::string("4"); break;
    //                }
    //                case AF_INET6:
    //                {
    //                    sockaddr_in6 *saddr = (sockaddr_in6*)cur_ai->ai_addr;
    //                    inet_ntop(cur_ai->ai_family, &(saddr->sin6_addr), buf,
    //                    bufSize); familyStr = std::string("6"); break;
    //                }
    //                default:
    //                    assert(false);
    //                    break;
    //            }
    //            const std::string protocolStr = (cur_ai->ai_protocol ==
    //            IPPROTO_UDP) ? std::string("udp") : std::string("tcp");
    //            fmt::print("IPv{}: {} protocol: {}\n", familyStr, buf,
    //            protocolStr);
    //        }
    //    }
    //
    //    const auto IPv6Size = sizeof(sockaddr_in6);//28
    //    const auto IPv4Size = sizeof(sockaddr_in);//16
    //    const auto sockaddrSize = sizeof(sockaddr);//16
    //    fmt::print("IPv6Size: {}\nIPv4Size: {}\nsockaddrSize: {}", IPv6Size,
    //    IPv4Size, sockaddrSize);

    //    struct sockaddr_in si_other;
    //    int s;
    //    socklen_t slen = sizeof(si_other);
    //    char buf[BUFLEN];
    //    char message[BUFLEN];
    //
    //    if ((s = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP)) == -1)
    //    {
    //        die("socket");
    //    }
    //
    //    memset((char *)&si_other, 0, sizeof(si_other));
    //    si_other.sin_family = AF_INET;
    //    si_other.sin_port = htons(PORT);
    //
    //    if (inet_aton(SERVER, &si_other.sin_addr) == 0)
    //    {
    //        fprintf(stderr, "inet_aton() failed\n");
    //        exit(1);
    //    }
    //
    //    while (1)
    //    {
    //        printf("Enter message : ");
    //        gets(message);
    //
    //        // send the message
    //        if (sendto(s, message, strlen(message), 0, (struct
    //        sockaddr*)&si_other, slen) == -1)
    //        {
    //            die("sendto()");
    //        }
    //
    //        // receive a reply and print it
    //        // clear the buffer by filling null, it might have previously
    //        received
    //        // data
    //        memset(buf, '\0', BUFLEN);
    //        // try to receive some data, this is a blocking call
    //        if (recvfrom(s, buf, BUFLEN, 0, (struct sockaddr *)&si_other,
    //        &slen) == -1)
    //        {
    //            die("recvfrom()");
    //        }
    //
    //        puts(buf);
    //    }
    //
    //    close(s);

    try
    {
        std::string userMsg;
        net::UDP::Socket s = net::UDP::Socket(net::UDP::V4(), 111);
        net::Address sender;
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
            s.sendTo(net::Address(net::kIPv4Loopback, PORT), userMsg.data(),
                     userMsg.size());

            const auto bytesRecieved = s.recvFrom(buf, kBufSize, sender);
            buf[bytesRecieved] = '\0';
            fmt::print("Recieved from: {}\n", sender.port());
            fmt::print("Content: {}", (char *)(buf));
        }
    }
    catch (const net::exception::RuntimeError &re)
    {
        std::cout << re;
    }
    catch (const net::exception::LogicError &le)
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
