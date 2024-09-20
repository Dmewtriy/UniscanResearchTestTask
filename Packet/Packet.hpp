#pragma once
#include <stdexcept>
#include <cstring>

// Структура, представляющая пакет с числовой идентификацией
struct Packet
{
public: 
    unsigned char* data; // данные пакета
    unsigned int dataCount; // длина пакета
    unsigned int packetId; // идентификатор пакета
    Packet* next; // Указатель на следующий узел
    // Конструктор структуры с проверкой на размер пакета
    Packet(const unsigned char* data, unsigned int dataCount, unsigned int packetId);
    // Конструктор копирования
    Packet(const Packet& packet);
    // Оператор присваивания копированием
    Packet& operator=(const Packet& packet);
    // Деструктор
    ~Packet();
};