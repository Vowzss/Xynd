#pragma once

#include "pch.h"

#include <iostream>
#include <spdlog/spdlog.h>

#include "packets/packet.h"

class Sockets
{
public:
    static void close(const int& pHandle)
	{
		#ifdef _WIN32
        ::closesocket(pHandle);
		#else
		::close(pHandle);
		#endif
	}
	
	static bool bind(const int& pHandle, const sockaddr_in& pAddress, const socklen_t& pLength)
	{
		int rs = ::bind(pHandle, (sockaddr*)&pAddress, pLength);
		if (rs == -1) {
            spdlog::error("Failed to bind socket! > {}", errno);
			return false;
        }

		return true;
	}

	static bool send(const int& pHandle, const sockaddr_in& pAddress, const packet& pPacket)
	{
		std::vector<char> packet = pPacket.serialize();
		
		int rs = ::sendto(pHandle, packet.data(), packet.size(), 0, (struct sockaddr*)&pAddress, sizeof(pAddress));
        if (rs == -1) {
            spdlog::warn("Failed to send packet! > {}", errno);
			return false;
        }

		return true;
	}

	static bool receive(const int& pHandle, const sockaddr_in& pAddress, char* buffer)
	{
		memset(&buffer, 0, sizeof(buffer));

		const int rs = ::recvfrom(pHandle, buffer, sizeof(buffer), 0, (sockaddr*)&pAddress, (socklen_t*)sizeof(pAddress));

        if (rs == 0) {
			spdlog::warn("Connection closed by remote host");
			return false;
		}
		else if (rs == -1) {
			//spdlog::warn("Failed receiving data! > {}", errno);
			return false;
		}

		return true;
	}
};