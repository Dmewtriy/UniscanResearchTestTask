#include "Packet.hpp"


Packet::Packet(const unsigned char* data, unsigned int dataCount, unsigned int packetId)
{
    this->data = new unsigned char[dataCount]; 
    std::memcpy(this->data, data, dataCount);
    this->dataCount = dataCount;
    this->packetId = packetId;
    next = nullptr;
}


Packet::Packet(const Packet& packet)
{
    dataCount = packet.dataCount;
    data = new unsigned char[dataCount];
    for (size_t i = 0; i < dataCount; i++)
    {
        data[i] = packet.data[i];
    }
    packetId = packet.packetId;
    next = nullptr;
}


Packet& Packet::operator=(const Packet& packet)
{
    dataCount = packet.dataCount;
    data = new unsigned char[dataCount];
    for (size_t i = 0; i < dataCount; i++)
    {
        data[i] = packet.data[i];
    }
    packetId = packet.packetId;
    next = nullptr;
    return *this;
}


Packet::~Packet()
{
    delete[] data;
}