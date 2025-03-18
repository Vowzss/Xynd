#pragma once
#include "pch.h"
#include "network.h"

struct sock_config
{
    int family;
    int type;
    int protocol;
};

class Socket
{
protected:
    int handle = -1;

protected:
    Socket(const sock_config& pConfig)
    {
        handle = ::socket(pConfig.family, pConfig.type, pConfig.protocol);
    }

    virtual ~Socket() 
    {
        close();
    }

public:
    void close()
    {
    #ifdef _WIN32
        ::closesocket(handle);
    #else
        ::close(handle);
    #endif
    }
};

class ServerSocket : public Socket
{
private:
    const sockaddr_in* sv_addr;
    socklen_t sv_length;

    char buffer[1024]; 

    sockaddr_in cl_addr;
    socklen_t cl_length;
    
public:
    ServerSocket(const sock_config& pConfig, const sockaddr_in* pAddress) : Socket(pConfig)
    {
        sv_addr = pAddress;
        sv_length = sizeof(pAddress);

        if (::bind(handle, (sockaddr*)&pAddress, sv_length) == -1) {
            throw std::runtime_error("Cannot bind socket: " + std::string(strerror(errno)));
        }

        cl_length = sizeof(cl_addr);
        memset(&cl_addr, 0, sizeof(cl_length));
    }
    ~ServerSocket() override 
    {

    }

    void listen() 
    {
        memset(&buffer, 0, sizeof(buffer));

        const int data = ::recvfrom(handle, buffer, sizeof(buffer), 0, (sockaddr*)&cl_addr, &cl_length);
        if (data == -1) {
            std::cout << "Error receiving data! Error:" << strerror(errno) << "\n";
            return;
        }
    
        // TODO: handle protobuf message here
        std::cout << "Message received from " << Network::getIpAddress(cl_addr) << " : " << buffer <<"\n";
    }
};

class ClientSocket : public Socket
{
public:
    ClientSocket(const sock_config& pConfig) : Socket(pConfig)
    {
        
    }
    ~ClientSocket() override
    {

    }

    void send(const sockaddr_in& pAddress, const char* pPacket) 
    {
        int rs = ::sendto(handle, pPacket, sizeof(pPacket) + 1, 0, (struct sockaddr*)&pAddress, sizeof(pAddress));
        if (rs < 0) {
            std::cerr << "Cannot send packet! " << strerror(errno) << "\n";
        }
    }

    inline void send(const std::string packet) 
    { 
        send(packet.c_str());
    }
};