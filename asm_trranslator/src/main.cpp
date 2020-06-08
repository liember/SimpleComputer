#include <iostream>
#include <fstream>
#include <ctype.h>

#include <vector>

#include "StringSwitch.hpp"

using namespace std;

constexpr int max_mem = 100;

enum comands_code
{
    read = 0x10,
    write = 0x11,
    load = 0x20,
    store = 0x21,
    add = 0x30,
    sub = 0x31,
    divide = 0x32,
    mul = 0x33,
    jump = 0x40,
    jneg = 0x41,
    jz = 0x42,
    halt = 0x43,
    AND = 0x52,
    SET_VARIABLE
};

int check_list_size = 13;
static constexpr int8_t check_list[] = {comands_code::read,
                                        comands_code::write,
                                        comands_code::load,
                                        comands_code::store,
                                        comands_code::add,
                                        comands_code::sub,
                                        comands_code::divide,
                                        comands_code::mul,
                                        comands_code::jump,
                                        comands_code::jneg,
                                        comands_code::jz,
                                        comands_code::halt,
                                        comands_code::AND};

int Encode(int8_t command, int8_t operand, int16_t *value)
{
    if (operand > max_mem)
    {
        cout << "[!] Operand address exceeds memory size" << endl;
        return 1;
    }

    bool command_is_defined = true;
    for (int i = 0; i < check_list_size; i++)
    {
        if (command == check_list[i])
        {
            command_is_defined = true;
        }
    }
    if (!command_is_defined)
    {
        cout << "[!] Unsupported command" << endl;
        return 1;
    }
    *value = 0;
    *value = (command << 7) | operand;
    *value = *value | (int16_t)0x4000;
    return 0;
}

struct order_t
{
    int16_t addres;
    string comand;
    int8_t operand;
    order_t(int16_t a, string b, int8_t c) : addres(a), comand(b), operand(c) {}
};

struct asm_cmd
{
    int16_t addres;
    int8_t comand;
    int8_t operand;
    asm_cmd(int16_t a, int8_t b, int8_t c) : addres(a), comand(b), operand(c) {}
};

struct asm_var
{
    int16_t value;
    int16_t addres;
};

asm_cmd Translate(order_t *ord)
{
    asm_cmd cmd(0, 0, 0);
    ss_switch(ord->comand)
    {
        ss_case("READ") : cmd.comand = comands_code::read;
        break;
        ss_case("WRITE") : cmd.comand = comands_code::write;
        break;
        ss_case("LOAD") : cmd.comand = comands_code::load;
        break;
        ss_case("STORE") : cmd.comand = comands_code::store;
        break;
        ss_case("ADD") : cmd.comand = comands_code::add;
        break;
        ss_case("SUB") : cmd.comand = comands_code::sub;
        break;
        ss_case("DIVIDE") : cmd.comand = comands_code::divide;
        break;
        ss_case("MUL") : cmd.comand = comands_code::mul;
        break;
        ss_case("JUMP") : cmd.comand = comands_code::jump;
        break;
        ss_case("JNEG") : cmd.comand = comands_code::jneg;
        break;
        ss_case("JZ") : cmd.comand = comands_code::jz;
        break;
        ss_case("HALT") : cmd.comand = comands_code::halt;
        break;
        ss_case("AND") : cmd.comand = comands_code::AND;
        break;
        ss_case("=") : cmd.comand = comands_code::SET_VARIABLE;
        break;
    }
    cmd.operand = ord->operand;
    cmd.addres = ord->addres;
    return cmd;
}

int main(int argc, char **argv)
{

    vector<order_t> program;
    int16_t max_addr = -1;

    std::ifstream in(argv[1]);
    if (in.is_open())
    {

        int addres;
        string comand;
        int operand;

        cout << "[?] Start translation:" << endl
             << "#####################" << endl;

        while (in >> addres >> comand >> std::hex >> operand)
        {
            if (addres < max_mem)
            {
                if (addres > max_addr)
                {
                    max_addr = addres;
                }

                cout << "Order with:" << endl
                     << "addres : " << addres << endl
                     << "comand: " << comand << endl
                     << "operand: " << operand << endl;
                cout << " ------------------------ " << endl;
                program.push_back(order_t(addres, comand, operand));
            }
            else
            {
                cout << "[!] Addres [" << addres << "] more than device memory" << endl;
                cout << "[ Info ]" << endl
                     << " ADDRES: " << addres
                     << endl
                     << " COMAND: " << comand
                     << endl
                     << " OPERAND: " << operand
                     << endl;
            }
        }
    }
    else
    {
        cout << "[!] File not found" << endl;
    }

    in.close();

    if (program.size() > max_mem)
    {
        cout << "[!] Program more than device memory" << endl;
        return 1;
    }

    int16_t asmcode[max_addr];
    for (size_t i = 0; i < program.size(); i++)
    {
        int16_t code;

        asm_cmd cmd = Translate(&program[i]);

        if (cmd.comand == comands_code::SET_VARIABLE)
        {
            asmcode[cmd.addres] = cmd.operand;
        }
        else if (Encode(cmd.comand, cmd.operand, &code) == 0)
        {
            asmcode[cmd.addres] = code;
        }
        else
        {
            cout << "[ Info ]" << endl
                 << " ADDRES: " << program[i].addres
                 << endl
                 << " COMAND: " << program[i].comand
                 << endl
                 << " OPERAND: " << program[i].operand
                 << endl;
        }
    }

    std::ofstream out("testcode.bin", ios::binary | ios::out);
    if (out.is_open())
    {
        for (int i = 0; i < program.size(); i++)
        {
            out.write((char *)&asmcode[i], sizeof(int16_t));
        }
    }
    out.close();
}