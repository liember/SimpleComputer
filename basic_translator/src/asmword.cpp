#include "asmword.hpp"

asmword::asmword(int *a, std::string n, int *o)
{
    addr = a;
    name = n;
    operand = o;
}

asmword::~asmword()
{
}

void asmword::Print()
{
    std::cout << "[ "
              << (addr == nullptr ? 0 : *addr) << " ] "
              << name;
    if (operand == nullptr)
    {
        std::cout << std::endl;
    }
    else
    {
        std::cout << " [ " << *operand << " ]" << std::endl;
    }
}

std::string asmword::GenerateCodeString()
{
    std::string result;

    result += std::to_string(*addr) + " " + name;

    if (operand == nullptr)
    {
        return result;
    }

    result += " " + std::to_string(*operand);

    return result;
}