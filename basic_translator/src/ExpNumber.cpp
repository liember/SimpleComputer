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

void expressions::number_expression::RegValues()
{
    library::addressTable::Add(value);
}