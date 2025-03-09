#pragma once

struct sockaddr_in;

class Toolbox {
public:
	static char* GetIpAddressFromBytes(const sockaddr_in& addr);
};