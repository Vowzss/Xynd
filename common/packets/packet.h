#pragma once
#include <vector>

#include "utils/constants.h"

class packet
{
private:
    char data[BUFFER_CAPACITY];

protected:
    packet() = default;
    virtual ~packet() = default;

public:
    virtual size_t size() const {
        return sizeof(*this);
    }

    virtual std::vector<char> serialize() const = 0;
};