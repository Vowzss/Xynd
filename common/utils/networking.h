#pragma once

#include "pch.h"

class Networking
{
public:
	static std::string getIpAddress(const sockaddr_in& addr)
	{
		char address[256];
    	memset(address, 0, sizeof(address));
    
	#ifdef _WIN32
		inet_ntop(AF_INET, &addr.sin_addr.s_addr, address, sizeof(address));
	#else
		inet_ntop(AF_INET, &addr.sin_addr, address, sizeof(address));
	#endif

		return address;
	}

	#ifdef _WIN32
	static void startWinsock() 
	{
		WSADATA data;
		constexpr WORD version = MAKEWORD(2, 2);
		
		if (WSAStartup(version, &data)) {
			printf( "WSAStartup failed: %d", WSAGetLastError() );
			return;
		}
	}
	static void stopWinsock()
	{
		WSACleanup();
	}
	#endif
};