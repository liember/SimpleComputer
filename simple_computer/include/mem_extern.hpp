#pragma once

#include <cstdint>
#include <exception>
#include <iostream>

#define TOO_FULL 0x01
#define ZERO_DIVIDE 0x02
#define OVER_THE_BORDER 0x03
#define IGNORE 0x04
#define WRONG_COMMAND 0x05
#define FILE_FAIL 0x06

#define ERR_WRONG_ADDR -1
#define ERR_OPEN_FILE -2
#define ERR_FILE_SIZE -3
#define ERR_UNCORRECT_COMMAND -4
#define ERR_ATTRIBUTE_BIT -5
#define ERR_WRONG_FLAG -6

namespace external_memory
{

inline constexpr uint16_t standart_memory_size = 100;

class RandomAcsessMemory
{
public:
    int16_t *memory;

    const int size;

    RandomAcsessMemory();
    explicit RandomAcsessMemory(int size);
    ~RandomAcsessMemory();

    void Init();

    void Set(int, uint16_t);
    int16_t Get(unsigned int);

    void Save(const char *);
    void Load(const char *);
};

class Interface
{
public:
    RandomAcsessMemory ram;
    void Init();
    Interface();
    explicit Interface(int ram_size);
};

} // namespace external_memory