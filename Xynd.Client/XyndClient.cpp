// Ensure linker includes the required library
#include <iostream>
#include <ws2tcpip.h>

#include "toolbox.h"

#pragma comment(lib, "Ws2_32.lib")

int main(int argc, char* argv[])
{
    // Initialize winsock
    WSADATA data;
    constexpr WORD version = MAKEWORD(2, 2);
    
    if (WSAStartup(version, &data) != 0) {
        std::cout << "Cannot start Winsock!\n";
        return 0;
    }

    // Server information
    sockaddr_in server_addr;
    server_addr.sin_addr.s_addr = INADDR_ANY;
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(27015); // Convert from little to big endian
    inet_pton(AF_INET, "127.0.0.1", &server_addr.sin_addr);

    // Create socket
    const SOCKET out = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);

    std::string s(argv[1]);
    int send = sendto(out, s.c_str(), s.size() + 1, 0, (struct sockaddr*)&server_addr, sizeof(server_addr));

    if (send == SOCKET_ERROR)
    {
        std::cout << "Cannot send data! " << WSAGetLastError() << "\n";
    }

    // Close socket
    closesocket(out);

    // Cleanup winsock
    WSACleanup();
}
