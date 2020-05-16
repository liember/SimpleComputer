#pragma once

#include <map>
#include <string>

#include <iostream>

namespace library
{

    enum types
    {
        ConstantValue,
        VariableValue
    };

    namespace
    {
        class value
        {
        private:
            int address;

        public:
            const std::string name;
            const int val;
            const int type;

            value(std::string n, int v, int type);

            bool IsIt(std::string val);
            int Type();

            void SetAddr(int addr);
            int *GetAddr();

            void Print();
        };

        class constantValue final : public value
        {
        public:
            constantValue(int name);
        };

        class mutableValue final : public value
        {
        public:
            mutableValue(char name);
        };
    } // namespace

    class addressTable
    {

    public:
        std::map<std::string, value *> values;

        bool Add(int v);  // false if value already exists
        bool Add(char v); // false if value already exists

        void Print();

        int *Query(int v);
        int *Query(char v);
    };

} // namespace library