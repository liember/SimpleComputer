#pragma once

#include <cstdint>
#include <exception>
#include <iostream>
#include <memory>
#include <array>

namespace Memory
{

    namespace Errors
    {
        class UndefIndex : virtual public std::exception
        {
        protected:
            int index;

        public:
            explicit UndefIndex(int i)
            {
                index = i;
            }
            virtual ~UndefIndex() throw() {}

            const int GetVal() const throw()
            {
                return index;
            }
        };

        class SizeFailrule : virtual public std::exception
        {
        protected:
            int index;

        public:
            explicit SizeFailrule(int i)
            {
                index = i;
            }
            virtual ~SizeFailrule() throw() {}

            const int GetVal() const throw()
            {
                return index;
            }
        };
    } // namespace Errors

    inline constexpr uint16_t max_mem_size = 128;
    // standart memory value (if does not set by user)
    inline constexpr uint16_t standart_memory_size = 100;

    class RandomAcsessMemory
    {
    private:
        std::unique_ptr<int16_t[]> memory;

        int err_info;

    public:
        const int size;

        RandomAcsessMemory();
        explicit RandomAcsessMemory(int size);
        ~RandomAcsessMemory();

        void Init();

        void Set(int, uint16_t);
        int16_t Read(unsigned int) const;
        int GetErr() const { return err_info; }

        void Save(const char *);
        void Load(const char *);
    };

    // contain value
    class ValRegister
    {
    private:
        int16_t cell;

        bool modified;

    public:
        ValRegister();
        bool isModified() const { return modified; }
        void Set(int16_t v);
        int16_t Read() const;
    };

    // may contain up to 8 flags
    class FlagRegisters
    {
    private:
        uint8_t flags;

        bool modified;

    public:
        void Init();
        bool isModified() const { return modified; }
        int Read(uint8_t regist) const;
        void Set(uint8_t regist, bool value);
    };

} // namespace Memory
