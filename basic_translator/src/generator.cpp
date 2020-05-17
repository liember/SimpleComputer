#include "Generator.hpp"
#include <vector>

Generator::Generator(variables *v, statements *s)
{
    vars = v;
    states = s;
}

Generator::~Generator()
{
}

void Generator::PreGenerate()
{
    for (auto &&i : *states)
    {
        std::vector<asmword *> *vec = i->GenerateAsm(vars, states);
        for (auto &&i : *vec)
        {
            command_list.push_back(i);
            current_asm_addr++;
        }
    }
}

void Generator::Generate(std::string output_file_name)
{
    std::ofstream out(output_file_name);
}