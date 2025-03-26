#pragma once

#include <array>
#include <vector>
#include <spdlog/spdlog.h>
#include <google/protobuf/message.h>

#include "packets/packet.h"
#include "protobuf/position_packet.pb.h"

class position_packet : public packet 
{
private:
    float x, y, z;

public:
    position_packet(float pX, float pY, float pZ) : packet(), x(pX), y(pY), z(pZ)
    {
    }

    position_packet(const std::array<float, 3>& pPosition) : packet()
    {
        x = pPosition[0];
        y = pPosition[1];
        z = pPosition[2];
    }

    position_packet(const std::vector<float>& pPosition) : packet()
    {
        if (pPosition.size() < 3) {
            spdlog::error("Vector size is smaller than 3 elements.");
            return;
        }

        x = pPosition[0];
        y = pPosition[1];
        z = pPosition[2];
    }

    std::vector<char> serialize() const override {
        PositionPacket message;
        message.set_x(x);
        message.set_y(y);
        message.set_z(z);

        std::string data;
        if (!message.SerializeToString(&data)) {
            spdlog::error("Failed to serialize PositionPacket!");
            throw std::exception();
        }

        std::vector<char> packet = {};
        packet.assign(data.begin(), data.end());
        return packet;
    }
};