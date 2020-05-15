#include "parser.hpp"

using namespace parsing::AST;

EndStatement::EndStatement(int a)
{
    address = a;
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

void EndStatement::RegValues()
{
}