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
    return value;
}

int expressions::variable_expression::GetType()
{
    return expressions::types::MutableValue;
}

void expressions::variable_expression::RegValues(library::addressTable *lib)
{
    lib->Add(value);
}

int *expressions::variable_expression::Requre(library::addressTable *lib)
{
    return lib->Query(value);
}

std::vector<asmword *> *expressions::variable_expression::GenerateAsm(library::addressTable *variables, library::value_heap *heap)
{
    std::cout << "[ CRITICAL WARNING ] This code should never have been run [ variable_expression::GenerateAsm() ]" << std::endl;
    return nullptr;
}
