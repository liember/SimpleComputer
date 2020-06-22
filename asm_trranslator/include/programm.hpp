#pragma once

#include "order.hpp"

#include <vector>
#include <fstream>
#include <sstream>
#include <string.h>

class programm
{
private:
    std::vector<order *> commands_list;
    int prev_addr;

    std::ifstream input_file;

public:
    void Read();
    int16_t *GetProgram();
    int GetSize();

    programm(std::string filename);
    ~programm();
};