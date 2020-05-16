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
