#include <iostream>

#include "network.h"
#include "socket.h"
#include "pch.h"

int main()
{
#ifdef _WIN32
    Network::startWinsock();
#endif

    // Server information
    sockaddr_in server_addr;
    memset(&server_addr, 0, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(27015);
    server_addr.sin_addr.s_addr = htons(INADDR_ANY);

    // Create socket
    sock_config sock_config;
    sock_config.family = AF_INET;       // Use IPv4
    sock_config.type = SOCK_DGRAM;      // Use UDP socket type
    sock_config.protocol = IPPROTO_UDP; // Use UDP protocol
    ServerSocket socket = ServerSocket(sock_config, &server_addr);

    std::cout << "Waiting for messages..." << "\n";
    while (true)
    {
        socket.listen();
    }
    
#ifdef _WIN32
    Network::stopWinsock();
#endif
}
