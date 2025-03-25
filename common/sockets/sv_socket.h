#pragma once

#include "socket.h"
#include "utils/sockets.h"
#include "packets/packet.h"
#include "models/connection_info.h"

class sv_socket : public socket
{
private:
    char buffer[BUFFER_CAPACITY]; 

    sockaddr_in cl_addr;
    socklen_t cl_length;
    
public:
    sv_socket(const socket_param& pParams, connection_info pInfo) : socket(pParams, socket_type::server)
    {
        addr = pInfo.addr;
        addr_length = sizeof(pInfo.addr);

        Sockets::bind(handle, addr, addr_length);

        cl_length = sizeof(cl_addr);
        memset(&cl_addr, 0, sizeof(cl_length));
    }
    
    ~sv_socket() override
    {

    }

    /**
     * @brief Listen to any incomming data
     */
    void listen()
    {
        if (!Sockets::receive(handle, cl_addr, buffer))
            return;
        
        // TODO: handle protobuf message here
        std::cout << "Message received from " << Networking::getIpAddress(cl_addr) << " : " << buffer <<"\n";
    }
};