#pragma once
#include "Packet.hpp"

// Шаблонный класс, который реализует логику очереди пакетов с числовой идентификацией пакетов
// Через параметры шаблона задается максимальная длина одного пакета, 
// максимальное число пакетов в очереди и максимальный размер всей очереди пакетов в байтах
template<size_t MaxPacketSize, size_t MaxPacketCount, size_t MaxQueueSize>
class PacketQueue
{
private:
    Packet* front; // Указатель на начало очереди
    Packet* back; // Указатель на конец очереди
    size_t count; // Текущее количество пакетов в очереди
    size_t size; // Текущий размер пакетов в очереди в байтах
public:
    PacketQueue() : front(nullptr), back(nullptr), count(0), size(0) {};
    ~PacketQueue()
    {
        while (front != nullptr)
        {
            Packet* temp = front;
            front = front->next;
            delete temp;
        }
    }

    /*
    * @brief Помещает пакет в очередь
    * @param data Содержимое пакета
    * @param dataCount Длина пакета в байтах
    * @param packetId Идентификатор пакета
    * @return true, если пакет помещён в очередь, и false в ином случае
    */
    bool Push(unsigned char *data, unsigned int dataCount, unsigned int packetId)
    {
        // длина пакета превышает максимально допустимую, число пакетов в очереди или
        // суммарный размер пакетов в очереди превысили максимально допустимые
        if (dataCount > MaxPacketSize || count >= MaxPacketCount || size + dataCount > MaxQueueSize)
        {
            return false;
        }

        // Создаём новый пакет
        Packet* newPacket = new Packet(data, dataCount, packetId);

        // Если очередь не пуста, добавляем новый узел в конец
        if (back)
        {
            back->next = newPacket;
        }
        else
        {
            // Если очередь пуста, новый узел теперь передний
            front = newPacket;
        }
        
        back = newPacket; // Обновляем указатель на задний узел
        size += dataCount; // Увеличиваем общий размер очереди
        count++; // Увеличиваем количество пакетов в очереди
        return true;
    }

    /*
    * @brief Помещает пакет в очередь
    * @param packet Пакет, который надо поместить в очередь
    * @return true, если пакет помещён в очередь, и false в ином случае
    */
    bool Push(Packet packet)
    {
        // Копируем данные переданного пакета
        unsigned int dataCount, packetId;
        dataCount = packet.dataCount;
        packetId = packet.packetId;

        // длина пакета превышает максимально допустимую, число пакетов в очереди или
        // суммарный размер пакетов в очереди превысили максимально допустимые
        if (dataCount > MaxPacketSize || count >= MaxPacketCount || size + dataCount > MaxQueueSize)
        {
            return false;
        }

        // Создаём новый пакет
        Packet* newPacket = new Packet(packet);

        // Если очередь не пуста, добавляем новый узел в конец
        if (back)
        {
            back->next = newPacket;
        }
        else
        {
            // Если очередь пуста, новый узел теперь передний
            front = newPacket;
        }
        
        back = newPacket; // Обновляем указатель на задний узел
        size += dataCount; // Увеличиваем общий размер очереди
        count++; // Увеличиваем количество пакетов в очереди
        return true;
    }

    /*
    * @brief Извлекает пакет из очереди
    * @param buffer Приёмный буфер, куда помещаются данные, извлечённые из очереди
    * @param bufferSize Размер приёмного буфера
    * @param dataCount Фактический рамезр пакета, извлечённого из очереди
    * @param packetId Идентификатор пакета, извлечённого из очереди
    * @return true, если пакет извлечён и помещён в буфер, и false, если очередь пуста
    */
    bool Pop(unsigned char *buffer, unsigned int bufferSize, unsigned int &dataCount, unsigned int &packetId)
    {
        // Если очередь пустая, возвращаем false
        if (count == 0) return false;

        // Извлекаем пакет из очереди и передвигаем указатель первого элемента
        Packet* temp = front;
        front = front->next;

        // Если в очереди был один элемент, то теперь она пустая
        if (front == nullptr) back = nullptr;

        // Помещаем в буфер данные из пакета соответсвующего размера
        if (bufferSize > 0)
        {
            if (bufferSize >= temp->dataCount)
            {
                std::memcpy(buffer, temp->data, temp->dataCount);
            }
            else
            {
                std::memcpy(buffer, temp->data, bufferSize);
            }
        }

        // Копируем данные извлекаемого пакета
        dataCount = temp->dataCount;
        packetId = temp->packetId;

        size -= temp->dataCount; // Уменьшаем общий размер очереди
        count--; // Уменьшаем количество элементов в очереди

        delete temp; // Удаляем извлечённый объект

        return true;
    }


    /*
* @brief Проверяет пуста ли очередь
* @return true, если очередь пуста, и false, если нет
*/
bool isEmpty() const
{
    return count == 0;
} 

/*
* @brief Возвращает размер очереди
*/
size_t getSize() const
{
    return size;
}

/*
* @brief Возвращает количество элементов в очереди
*/
size_t getCount() const
{
    return count;
}
};