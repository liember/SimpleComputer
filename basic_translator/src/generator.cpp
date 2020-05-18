#include "Generator.hpp"
#include <vector>
#include <fstream>

Generator::Generator(variables *v, statements *s)
{
    vars = v;
    states = s;
    current_asm_addr = 0;
}

Generator::~Generator()
{
}

void Generator::PreGenerate()
{
    for (auto &&i : *states)
    {
        std::vector<asmword *> *vec = i->GenerateAsm(vars, states);
        for (auto &&b : *vec)
        {
            if (b->addr == nullptr)
                b->addr = new int(current_asm_addr);
            else
                *b->addr = current_asm_addr;
            command_list.push_back(b);
            current_asm_addr++;
        }
    }
}

void Generator::Generate(std::string output_file_name)
{
    std::ofstream out(output_file_name);
}

void Generator::Preview()
{

    for (auto &&i : command_list)
        i->Print();
    std::cout << std::endl;
    std::cout << "[ INFO ] Summary code size [" << command_list.size()
              << " ]" << std::endl;
}

void Generator::WriteToFile(std::string filename)
{
    std::ofstream file(filename);

    if (file.is_open())
        for (auto &&i : command_list)
            file << i->GenerateCodeString() + "\n";

    file.close();
}