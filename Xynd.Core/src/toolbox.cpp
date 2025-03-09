#include "pch.h"
#include "toolbox.h"

#include <ws2tcpip.h>

char* Toolbox::GetIpAddressFromBytes(const sockaddr_in& addr)
{
    char ip_address[256];
    ZeroMemory(ip_address, sizeof(ip_address));
    inet_ntop(AF_INET, &addr.sin_addr.s_addr, ip_address, sizeof(ip_address));

    return ip_address;
}
