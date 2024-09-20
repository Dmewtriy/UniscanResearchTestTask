#include <iostream>
#include <queue>
#include "PacketQueue.hpp"

int main()
{
    const size_t MaxPacketSize = 20;
    const size_t MaxPacketCount = 25;
    const size_t MaxQueueSize = 500;
    PacketQueue<MaxPacketSize, MaxPacketCount, MaxQueueSize>* queue = new PacketQueue<MaxPacketSize, MaxPacketCount, MaxQueueSize>;
    unsigned char data[] = "Information";
    Packet newPacket{data, sizeof(data), 123};

    if (queue->Push(newPacket))
    {
        std::cout << "Пакет помещён в очередь" << std::endl;
    } 
    else 
    {
        std::cout << "Ошибка при добавлении пакета в очередь" << std::endl;
    } 

    if (queue->Push(newPacket.data, newPacket.dataCount, newPacket.packetId))
    {
        std::cout << "Пакет помещён в очередь" << std::endl;
    }
    else
    {
        std::cout << "Ошибка при добавлении пакета в очередь" << std::endl;
    }
    
    unsigned char data2[] = "Important";
    if (queue->Push(data2, sizeof(data2), 1))
    {
        std::cout << "Пакет помещён в очередь" << std::endl;
    }
    else
    {
        std::cout << "Ошибка при добавлении пакета в очередь" << std::endl;
    }

    std::cout << queue->getCount() << ' ' << queue->getSize() << ' ' << queue->isEmpty() << std::endl;

    unsigned char buffer[6];
    size_t bufferSize = 6;
    uint dataCount, packetId;

    if (queue->Pop(buffer, bufferSize, dataCount, packetId))
    {
        std::cout << "Пакет извлечён из очереди" << std::endl;
    }
    else
    {
        std::cout << "Очередь пуста" << std::endl;
    }

    delete queue;
    queue = nullptr;
        
    return 0;
}
