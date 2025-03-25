#pragma once

#include "pch.h"

struct connection_info 
{
    sockaddr_in addr;

    connection_info(const uint& pFamily, const uint& pPort) 
    {
        memset(&addr, 0, sizeof(addr));

        addr.sin_family = pFamily;
        addr.sin_port = htons(pPort);
        addr.sin_addr.s_addr = INADDR_ANY;
    }
};