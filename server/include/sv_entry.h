#pragma once

class sv_socket;
struct connection_info;

class sv_entry
{
public:
    sv_socket* socket;

public:
    sv_entry(const connection_info& pInfo);
    ~sv_entry();

    void listen();
};