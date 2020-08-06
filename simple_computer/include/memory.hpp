#pragma once

#include <cstdint>
#include <exception>
#include <iostream>
#include <memory>
#include <array>

#include "exceptions.hpp"

namespace Memory
{

    inline constexpr uint16_t max_mem_size = 128;
    // standart memory value (if does not set by user)
    inline constexpr uint16_t standart_memory_size = 100;

    class RandomAcsessMemory
    {
    private:
        std::unique_ptr<int16_t[]> memory;

    public:
        const int size;

        RandomAcsessMemory();
        explicit RandomAcsessMemory(int size);
        ~RandomAcsessMemory();

        void Init();

        void Set(int, uint16_t);
        int16_t Read(unsigned int);

        void Save(const char *);
        void Load(const char *);
    };

    // contain value
    class ValRegister
    {
    private:
        int16_t cell;

    public:
        ValRegister();

        void Set(int16_t v);
        int16_t Read();
    };

    // may contain up to 8 flags
    class FlagRegisters
    {
    private:
        uint8_t flags;

    public:
        void Init();
        int Read(uint8_t regist);
        void Set(uint8_t regist, bool value);
    };

} // namespace Memory




