#include "parser.hpp"

using namespace parsing::AST;

expressions::number_expression::number_expression(int val) : value(val)
{
}

expressions::number_expression::~number_expression()
{
}

void expressions::number_expression::Print()
{
    std::cout << "Num: [" << value << "] ";
}

int expressions::number_expression::Eval()
{
    return value;
}

int expressions::number_expression::GetType()
{
    return expressions::types::ConstValue;
}

void expressions::number_expression::RegValues(library::addressTable *lib)
{
    lib->Add(value);
}

int *expressions::number_expression::Requre(library::addressTable *lib)
{
    return lib->Query(value);
}

std::vector<asmword *> *expressions::number_expression::GenerateAsm(library::addressTable *variables, library::value_heap *heap)
{
    std::cout << "[ CRITICAL WARNING ] This code should never have been run [ number_expression::GenerateAsm() ]" << std::endl;
    return nullptr;
}