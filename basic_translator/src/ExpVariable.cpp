#include "parser.hpp"

using namespace parsing::AST;

expressions::variable_expression::variable_expression(char val) : value(val)
{
}

expressions::variable_expression::~variable_expression()
{
}

void expressions::variable_expression::Print()
{
    std::cout << "Var: " << value << " ";
}

int expressions::variable_expression::Eval()
{
    return 0;
}

int expressions::variable_expression::GetType()
{
    return expressions::types::MutableValue;
}

void expressions::variable_expression::RegValues(library::addressTable *lib)
{
    lib->Add(value);
}
