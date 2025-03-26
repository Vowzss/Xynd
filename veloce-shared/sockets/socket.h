#pragma once

#include "utils/sockets.h"
#include "utils/networking.h"

#include "enums/socket_type.h"
#include "models/socket_param.h"

class socket
{
protected:
    sockaddr_in addr;
    socklen_t addr_length;

    uint handle = -1;

private:
    socket_param params;
    socket_type type;

protected:
    socket(const socket_param& pParams, const socket_type& pType)
    {
        params = pParams;
        type = pType;

        handle = ::socket(pParams.family, pParams.type, pParams.protocol);
    }

    virtual ~socket()
    {
        close();
    }

public:
    void close()
    {
    #ifdef _WIN32
        ::closesocket(handle);
    #else
        ::close(handle);
    #endif
    }
};