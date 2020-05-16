#include "Generator.hpp"

Generator::Generator(variables *v, statements *s)
{
    vars = v;
    states = s;
}

Generator::~Generator()
{
    delete vars;
    delete states;
}

void Generator::Generate(std::string output_file_name)
{
    std::ofstream out(output_file_name);
}