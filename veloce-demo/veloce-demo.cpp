#include <functional>
#include <thread>

#include "cl_entry.h"
#include "sv_entry.h"

#include "utils/networking.h"
#include "models/connection_info.h"
#include "packets/position_packet.h"

int main(int argc, char* argv[])
{
#ifdef _WIN32
    Networking::startWinsock();
#endif

    // server information
    connection_info sv_info = connection_info(AF_INET, 27015);

    // create server socket & listen in background
    sv_entry* server = new sv_entry(sv_info);
    std::thread th([server]() {
        server->listen();
    });

    // create client socket & send a packet
    cl_entry* client = new cl_entry(sv_info);

    position_packet pkt = position_packet(0, 0, 0);
    client->send(pkt);

    // free memory
    delete client;
    client = nullptr;

    delete server;
    server = nullptr;

#ifdef _WIN32
    Networking::stopWinsock();
#endif
}