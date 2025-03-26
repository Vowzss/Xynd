#include <spdlog/spdlog.h>

#include "cl_entry.h"
#include "sockets/cl_socket.h"
#include "models/socket_param.h"

cl_entry::cl_entry(const connection_info& pInfo)
{
    spdlog::info("Starting client...");

    // set socket parameters
    socket_param cl_params;
    cl_params.family = AF_INET;       // Use IPv4
    cl_params.type = SOCK_DGRAM;      // Use UDP protocol
    cl_params.protocol = IPPROTO_UDP;

    // create socket
    cl_socket socket = cl_socket(cl_params);
    socket.set_target(pInfo);

    spdlog::info("Started client!");
}

cl_entry::~cl_entry()
{
    spdlog::info("Stopping client...");

    // shutdown socket
    socket->close();

    // cleanup memory
    delete socket;
    socket = nullptr;

    spdlog::info("Stopped client!");
}

void cl_entry::send(const packet& pPacket)
{
    socket->send(pPacket);
}