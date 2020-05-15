#include "library.hpp"

using namespace library;

value::value(std::string n, int v, int t) : name(n), val(v), type(t) {}

bool value::IsIt(std::string val)
{
    if (val == name)
        return true;
    return false;
}

int value::Type()
{
    return type;
}

void value::SetAddr(int addr)
{
    address = addr;
}

int value::GetAddr()
{
    return address;
}

constantValue::constantValue(std::string name) : value(name, std::atoi(name.c_str()), types::ConstantValue) {}
mutableValue::mutableValue(const char name) : value(std::string(1, name), 0, types::VariableValue) {}

bool addressTable::Add(std::string v)
{
    bool found = false;

    // for (auto &&i : values)
    // {
    //     if (i->IsIt(v))
    //     {
    //         found == true;
    //         break;
    //     }
    // }

    // if (!found)
    // {
    //     constantValue *new_value = new constantValue(v);
    //     values.push_back(new_value);
    // }
    // else
    // {
    //     return true;
    // }

    return false;

} // false if value already exists

bool addressTable::Add(char v)
{

    const std::string desired = std::string(1, v);

    bool found = false;

    // for (auto &&i : values)
    // {
    //     if (i->IsIt(desired))
    //     {
    //         found == true;
    //         break;
    //     }
    // }

    // if (!found)
    // {
    //     mutableValue *new_value = new mutableValue(v);
    //     values.push_back(new_value);
    // }
    // else
    // {
    //     return true;
    // }

    return false;

} // false if value already exists
