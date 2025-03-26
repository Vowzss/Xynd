#pragma once
#include <string>

class cl_socket;
class packet;
struct connection_info;

class cl_entry 
{
public:
    cl_socket* socket = nullptr;

public:
    cl_entry(const connection_info& pInfo);
    ~cl_entry();

    void send(const packet& pPacket);
};