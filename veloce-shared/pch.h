#pragma once

#ifdef _WIN32
	using uint = unsigned int;
	#include <winsock2.h>
	#include <ws2tcpip.h>

	#pragma comment(lib, "Ws2_32.lib")
#else
	#include <arpa/inet.h>
	#include <unistd.h>
#endif