#include "parser.hpp"

using namespace parsing::AST;

SetStatement::SetStatement(int addr, int val, int *asm_adr) : address(addr)
{
    value = val;
    asm_address = asm_adr;
}

SetStatement::~SetStatement()
{
}

void SetStatement::Print()
{
    std::cout << "[ " << address << " ] [ VALUE ] [ " << value << "] " << std::endl;
}

bool SetStatement::Analyze()
{
    static int EndCounter = 0;
    EndCounter++;
    if (EndCounter != 0)
        return false;

    return true;
}

void SetStatement::EvalExpression()
{
}

void SetStatement::RegValues(library::addressTable *lib)
{
}

void SetStatement::SetAddr(int a)
{
    *asm_address = a;
}

int *SetStatement::GetAddr()
{
    return asm_address;
}

int SetStatement::GetId()
{
    return address;
}

std::vector<asmword *> *SetStatement::GenerateAsm(library::addressTable *variables, std::vector<parsing::AST::Statement *> *statements)
{
    std::vector<asmword *> *ret = new std::vector<asmword *>;

    asmword *command = new asmword(asm_address, "=", &value);
    ret->push_back(command);

    return ret;
}