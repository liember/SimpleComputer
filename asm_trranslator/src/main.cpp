#include <iostream>
#include <fstream>
#include <memory>

#include "programm.hpp"

int main(int argc, char **argv)
{
    std::string inp_filename(argv[1]);
    std::string out_filename;

    if (argv[1] == nullptr)
    {
        std::cout << "[ WARNING ] Please input [ inputfile ]" << std::endl;
        return 1;
    }
    else if (inp_filename.substr(inp_filename.find_last_of(".") + 1) != "sasm")
    {
        std::cout << "[ WARNING ] File is not [ .sasm ] extention " << inp_filename << std::endl;
        return 1;
    }

    out_filename = inp_filename;
    auto mPos = out_filename.find('.');
    out_filename.replace(out_filename.begin() + mPos, out_filename.end(), ".bin");

    int16_t *bin;
    int bin_size;
    try
    {
        programm prog(inp_filename);
        prog.Read();
        bin = prog.GetProgram();
        bin_size = prog.GetSize();
    }
    catch (const std::exception &e)
    {
        std::cerr << e.what() << '\n';
    }

    std::ofstream out(out_filename, std::ios::out | std::ios::binary);
    out.write((char *)bin, bin_size * 2);
    out.close();
    return 0;
}