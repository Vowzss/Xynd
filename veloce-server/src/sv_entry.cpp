#include <thread>
#include <chrono> 
#include <spdlog/spdlog.h>

#include "sv_entry.h"
#include "sockets/sv_socket.h"
#include "models/socket_param.h"

sv_entry::sv_entry(const connection_info& pInfo)
{
    spdlog::info("Starting server...");

    // set socket parameters
    socket_param params;
    params.family = AF_INET;       // Use IPv4
    params.type = SOCK_DGRAM;      // Use UDP protocol
    params.protocol = IPPROTO_UDP;

    // create socket
    sv_socket socket = sv_socket(params, pInfo);
    
    spdlog::info("Started server!");
}

sv_entry::~sv_entry()
{
    spdlog::info("Stopping server...");

    // shutdown socket
    socket->close();

    // cleanup memory
    delete socket;
    socket = nullptr;

    spdlog::info("Stopped server!");
}

void sv_entry::listen() const
{
    spdlog::info("Waiting for messages...");

    while (true)
    {
        socket->listen();
        std::this_thread::sleep_for(std::chrono::seconds(1));
    }
}
