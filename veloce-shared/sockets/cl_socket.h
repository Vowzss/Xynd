#pragma once

#include "socket.h"
#include "utils/sockets.h"
#include "packets/packet.h"
#include "models/connection_info.h"

class cl_socket : public socket
{
public:
    cl_socket(const socket_param& pParams) : socket(pParams, socket_type::client)
    {
        
    }

    ~cl_socket() override
    {

    }

    /**
     * @brief Define the target to send packets to.
     * @param pAddress The address of the server.
     */
    void set_target(const connection_info& pInfo)
    {
        addr = pInfo.addr;
        addr_length = sizeof(pInfo.addr);
    }

    /**
     * @brief Send a custom packet to the target
     * @param pPacket The packet to send.
     */
    void send(const packet& pPacket) 
    {
        const size_t packet_size = sizeof(pPacket);
        if (packet_size > BUFFER_CAPACITY)
        {
            const size_t overflow = packet_size - BUFFER_CAPACITY;
            spdlog::error("Packet size is too big!");
            return;
        }

        Sockets::send(handle, addr, pPacket);
    }
};