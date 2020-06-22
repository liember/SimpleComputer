#include "programm.hpp"

void programm::Read()
{
    int line_counter = 0;
    std::string buf_line;
    while (std::getline(input_file, buf_line))
    {
        std::stringstream line(buf_line);
        int16_t addr;
        int16_t operand;
        std::string command;
        if (line >> addr >> command)
        {
            if (strcmp(command.c_str(), "HALT") != 0)
            {
                if (line >> operand)
                {
                }
                else
                {
                    throw Except("Not full arguments line " + std::to_string(line_counter + 1));
                }
            }

            if (addr <= prev_addr)
            {
                throw Except("Wrong addressation");
            }

            order *p = new order(addr, command, operand);
            commands_list.push_back(p);
        }
        else
        {
            throw Except("Not full arguments line " + std::to_string(line_counter));
        }
        line_counter++;
    }
}

int16_t *programm::GetProgram()
{
    int16_t *result = new int16_t[commands_list.size()];
    for (auto &&i : commands_list)
    {
        result[i->address] = i->GetBinary();
    }
    return result;
}

int programm::GetSize()
{
    return commands_list.size();
}

programm::programm(std::string filename) : input_file(filename)
{
    if (!input_file.is_open())
    {
        std::cout << "[!] File not found" << std::endl;
        throw Except("File not found");
    }

    prev_addr = -1;
}

programm::~programm()
{
    for (auto &&i : commands_list)
    {
        delete i;
    }
    input_file.close();
}