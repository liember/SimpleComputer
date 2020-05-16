#include "parser.hpp"

using namespace parsing::AST;

EndStatement::EndStatement(int a) : address(a)
{
}

EndStatement::~EndStatement()
{
}

bool EndStatement::Analyze()
{
    return true;
}

void EndStatement::Print()
{
    std::cout << "[ " << address << " ] [ END ] " << std::endl;
}

void EndStatement::EvalExpression()
{
}

void EndStatement::RegValues(library::addressTable *lib)
{
}

void EndStatement::SetAddr(int a)
{
    asm_address = a;
}

int *EndStatement::GetAddr()
{
    return &asm_address;
}

int EndStatement::GetId()
{
    return address;
}

std::vector<asmword *> *EndStatement::GenerateAsm(library::addressTable *variables, std::vector<parsing::AST::Statement *> *statements)
{
    std::vector<asmword *> *ret = new std::vector<asmword *>;
    asmword *command = new asmword(&asm_address, "HALT", nullptr);
    ret->push_back(command);
    return ret;
}