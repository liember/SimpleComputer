#include "parser.hpp"

using namespace parsing::AST;

InputStatement::InputStatement(int a, expressions::expression *e)
{
    address = a;
    var = e;
}

InputStatement::~InputStatement()
{
}

void InputStatement::Print()
{
    std::cout << "Address: [" << address << "] Ccommand: INPUT Variable: [";
    var->Print();
    std::cout << "] " << std::endl;
}

void InputStatement::EvalExpression()
{
}

bool InputStatement::Analyze()
{
    if (var->GetType() != expressions::types::MutableValue)
    {
        std::cout << "[ WARNING ] Incorrect expression: \n[ Address: " << address << "] [ INPUT ] > CONSTANT VALUE <" << std::endl;
        return false;
    }
    return true;
}

void InputStatement::RegValues()
{
}