/*
    Simple udp client
*/
//#include <arpa/inet.h>
//#include <stdio.h>   //printf
//#include <stdlib.h>  //exit(0);
//#include <string.h>  //memset
//#include <sys/socket.h>
//#include <unistd.h>

#include <iostream>

#include "GitInfo.h"
#include "Version.h"

#define SERVER "127.0.0.1"
#define BUFLEN 512  // Max length of buffer
#define PORT 8888   // The port on which to send data

// void die(char *s)
//{
//    perror(s);
//    exit(1);
//}

void printVersionInfo()
{
    std::cout << "Version: " << UDPClient::Version::str() << '\n';
    std::cout << "branch: " << UDPClient::GitInfo::branch() << '\n';
    std::cout << "SHA1: " << UDPClient::GitInfo::SHA1() << '\n';
    const std::string isDirty = UDPClient::GitInfo::isDirty()
                                    ? std::string("true")
                                    : std::string("false");
    std::cout << "IS_DIRTY: " << isDirty << std::endl;
}

int main(void)
{
    printVersionInfo();

    //    struct sockaddr_in si_other;
    //    int s, i;
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
    //        if (sendto(s, message, strlen(message), 0, (struct sockaddr
    //        *)&si_other,
    //                   slen) == -1)
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
    //        &slen) ==
    //            -1)
    //        {
    //            die("recvfrom()");
    //        }
    //
    //        puts(buf);
    //    }
    //
    //    close(s);
    return 0;
}
