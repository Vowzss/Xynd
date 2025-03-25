#pragma once

class cl_socket;
struct connection_info;

class cl_entry 
{
public:
    cl_socket* socket;

public:
    cl_entry(const connection_info& pInfo);
    ~cl_entry();
};