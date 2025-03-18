#include <iostream>

#include "pch.h"
#include "socket.h"

int main(int argc, char* argv[])
{
#ifdef _WIN32
    Network::startWinsock();
#endif

    // Server information
    sockaddr_in server_addr;
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = htons(INADDR_ANY);
    server_addr.sin_port = htons(27015);
    inet_pton(AF_INET, "127.0.0.1", &server_addr.sin_addr);

    // Create socket
    sock_config sock_config;
    sock_config.family = AF_INET;       // Use IPv4
    sock_config.type = SOCK_DGRAM;      // Use UDP socket type
    sock_config.protocol = IPPROTO_UDP; // Use UDP protocol
    ClientSocket socket = ClientSocket(sock_config);

    socket.send(server_addr, argv[1]);

#ifdef _WIN32
    Network::stopWinsock();
#endif
}
