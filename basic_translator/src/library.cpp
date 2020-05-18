#include "library.hpp"
#include <algorithm>

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

int *value::GetAddr()
{
    return &address;
}

void value::Print()
{
    std::cout << "Registered " << (type == types::ConstantValue ? " constant " : " mutable ") << " value: " << name << " - " << val << std::endl;
}

constantValue::constantValue(int name) : value(std::to_string(name), name, types::ConstantValue)
{
}

mutableValue::mutableValue(const char name) : value(std::string(1, name), 0, types::VariableValue)
{
}

bool addressTable::Add(int v)
{
    constantValue *new_value = new constantValue(v);
    values.insert({std::to_string(v), new_value});
    return true;
} // false if value already exists

bool addressTable::Add(char v)
{
    const std::string tostring(v, 1);
    mutableValue *new_value = new mutableValue(v);
    values.insert({tostring, new_value});
    return true;
} // false if value already exists

void addressTable::Print()
{
    for (auto &&i : values)
        i.second->Print();
    std::cout << "\nMount registered values: " << values.size() << " values" << std::endl;
}

int *addressTable::Query(int v)
{
    const std::string query_str = std::to_string(v);
    return values.find(query_str)->second->GetAddr();
}

int *addressTable::Query(char v)
{
    const std::string query_str = std::string(v, 1);
    return values.find(query_str)->second->GetAddr();
}

int *value_heap::Query()
{
    int *result = heap.top();
    current_address--;
    heap.pop();
    return result;
}

int *value_heap::Push()
{
    value_storage.push(current_address);

    int *address = &value_storage.top();

    heap.push(address);
    int *result = heap.top();
    max_heap_size = std::max(max_heap_size, (int)heap.size());
    current_address++;
    return result;
}

bool value_heap::isEnd()
{
    if (heap.size() == 0)
    {
        return true;
    }
    return false;
}

value_heap::value_heap() : current_address(0), max_heap_size(0) {}