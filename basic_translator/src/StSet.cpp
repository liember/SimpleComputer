#include "parser.hpp"

using namespace parsing::AST;

SetStatement::SetStatement(int addr, int val) : address(addr)
{
    value = val;
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
}

void SetStatement::EvalExpression()
{
}

void SetStatement::RegValues(library::addressTable *lib)
{
}