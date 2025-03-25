#include <iostream>
#include <functional>

#include "cl_entry.h"
#include "sv_entry.h"

#include "sockets/cl_socket.h"
#include "sockets/sv_socket.h"

#include "models/connection_info.h"

int main(int argc, char* argv[])
{
#ifdef _WIN32
    Network::startWinsock();
#endif

    // server information
    connection_info sv_info = connection_info(AF_INET, 27015);

    // create server socket & listen in background
    sv_entry server = sv_entry(sv_info);
    std::thread th(std::bind(&sv_entry::listen, &server));
        
    // create client socket & send a packet
    cl_entry client = cl_entry(sv_info);
    client.socket->send("test message from client");

#ifdef _WIN32
    Network::stopWinsock();
#endif
}