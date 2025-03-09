#include <iostream>
#include <ws2tcpip.h>

#include "toolbox.h"

// Ensure linker includes the required library
#pragma comment(lib, "Ws2_32.lib")

int main()
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

    // Create socket
    const SOCKET in = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
    
    // Bind socket to server information
    if (bind(in, (sockaddr*)&server_addr, sizeof(server_addr)) == SOCKET_ERROR) {
        std::cout << "Cannot bind socket!" << WSAGetLastError() << "\n";
        return 0;
    }

    std::cout << "Running on: " << Toolbox::GetIpAddressFromBytes(server_addr) << "\n";

    // Client information 
    sockaddr_in client_addr;
    int client_length = sizeof(client_addr);
    ZeroMemory(&client_addr, client_length);

    // Client data
    char buffer[1024];

    std::cout << "Waiting for messages..." << "\n";
    // Wait for incoming message
    while (true)
    {
        ZeroMemory(buffer, sizeof(buffer));

        // Receive message
        const int bytes_in = recvfrom(in, buffer, sizeof(buffer), 0, (sockaddr*)&client_addr, &client_length);

        if (bytes_in == SOCKET_ERROR) {
            std::cout << "Error receiving data! Error:" << WSAGetLastError() << "\n";
            continue;
        }

        // Process message
        std::cout << "Message received from " << Toolbox::GetIpAddressFromBytes(client_addr) << " : " << buffer <<"\n";
    }

    // Close socket
    closesocket(in);
    
    // Cleanup winsock
    WSACleanup();
}
