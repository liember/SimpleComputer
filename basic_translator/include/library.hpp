#pragma once

#include <vector>
#include <string>

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
            const std::string name;
            const int val;
            const int type;

            int address;

        public:
            value(std::string n, int v, int type);

            bool IsIt(std::string val);
            int Type();

            void SetAddr(int addr);
            int GetAddr();
        };

        class constantValue final : public value
        {
        public:
            constantValue(std::string name);
        };

        class mutableValue final : public value
        {
        public:
            mutableValue(char name);
        };
    } // namespace

    class addressTable
    {
    private:
        //static std::vector<value *> values;

    public:
        static bool Add(std::string v); // false if value already exists
        static bool Add(char v);        // false if value already exists
    };

} // namespace library