#pragma once

#include <iostream>

class asmword
{
public:
    int *addr;
    std::string name;
    int *operand;

    asmword(int *a, std::string name, int *o);
    ~asmword();
};