#pragma once

#include "memory.hpp"

#include <algorithm>
#include <exception>
#include <array>
#include <ctype.h>

namespace ALM
{
    enum Flags
    {
        interrupt,
        error,
    };

    enum comands
    {
        // input/output
        Read = 0x10,
        Write = 0x11,
        // moving
        load = 0x20,
        store = 0x21,

        // match
        add = 0x30,
        sub = 0x31,
        divide = 0x32,
        mul = 0x33,

        // controll flow
        jump = 0x40,
        jneg = 0x41,
        jz = 0x42,
        halt = 0x43,
        // logic
        And = 0x52,

        Empty = 0
    };

    static std::array<uint8_t, 14> check_list = {comands::Read,
                                                 comands::Write,
                                                 comands::load,
                                                 comands::store,
                                                 comands::add,
                                                 comands::sub,
                                                 comands::divide,
                                                 comands::mul,
                                                 comands::jump,
                                                 comands::jneg,
                                                 comands::jz,
                                                 comands::halt,
                                                 comands::And,
                                                 comands::Empty};

    namespace Errors
    {

        class ZeroDivizion : virtual public std::exception
        {
        protected:
            int divided;

        public:
            explicit ZeroDivizion(int value)
            {
                divided = value;
            }
            virtual ~ZeroDivizion() throw() {}

            const int GetVal() const throw()
            {
                return divided;
            }
        };

        class UndefinedCommand : virtual public std::exception
        {
        protected:
            int cmd;

        public:
            explicit UndefinedCommand(int16_t value)
            {
                cmd = value;
            }
            virtual ~UndefinedCommand() throw() {}

            const int GetVal() const throw()
            {
                return cmd;
            }
        };

        class Overflow : virtual public std::exception
        {
        protected:
            int overlowed_val;

        public:
            explicit Overflow(int value)
            {
                overlowed_val = value;
            }
            virtual ~Overflow() throw() {}

            const int GetVal() const throw()
            {
                return overlowed_val;
            }
        };
    } // namespace Errors

    class Executor
    {
    private:
        // error msg contains here
        std::string err_msg;

        // max val which can be calculated
        static constexpr int max_possible_value = 0x3fff;

        void Decode(const int16_t value);
        void Calculate(Memory::RandomAcsessMemory &data);

        // used for decode resultss
        uint8_t command;
        uint8_t operand;

        Memory::ValRegister instruction_counter;
        Memory::FlagRegisters state;

        // results of operation pools here
        // (it is buf0)
        Memory::ValRegister accamulator;

        // used for midle resuld of calculation
        Memory::ValRegister buf1;
        Memory::ValRegister buf2;
        Memory::ValRegister buf3;
        Memory::ValRegister buf4;
        Memory::ValRegister buf5;
        Memory::ValRegister buf6;

        // buffer for output values
        // (it is buf7)
        Memory::ValRegister output;

    public:
        // Get info functions (returns buffeers)
        const Memory::FlagRegisters GetState() const { return state; }
        const Memory::ValRegister GetInstruction() const { return instruction_counter; }
        const Memory::ValRegister GetAccamulator() const { return accamulator; }
        const Memory::ValRegister GetBuf1() const { return buf1; }
        const Memory::ValRegister GetBuf2() const { return buf2; }
        const Memory::ValRegister GetBuf3() const { return buf3; }
        const Memory::ValRegister GetBuf4() const { return buf4; }
        const Memory::ValRegister GetBuf5() const { return buf5; }
        const Memory::ValRegister GetBuf6() const { return buf6; }
        const Memory::ValRegister GetOutput() const { return output; }
        const std::string GetErr() const { return err_msg; }

        // Set interrupt flag - true
        void Interrupt();
        // sets instruction counter - 0
        void Restart();
        // make one step of execution
        int Tik(Memory::RandomAcsessMemory &data, Memory::RandomAcsessMemory &commands);

        std::string const GetErr();
    };

} // namespace ALM