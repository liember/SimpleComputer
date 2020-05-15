#include "parser.hpp"

using namespace parsing::AST;

LetStatement::LetStatement(int a, expressions::expression *e)
{
    address = a;
    expr = e;
}

bool LetStatement::Analyze()
{
    return true;
}

LetStatement::~LetStatement()
{
    delete expr;
}

void LetStatement::RegValues()
{
}

void LetStatement::Print()
{
    std::cout << "[ " << address << " ] [ LET ] [ ";
    expr->Print();
    std::cout << "] " << std::endl;
}

void LetStatement::EvalExpression()
{
    if (expr->GetType() == expressions::types::ConstExpression)
    {
        const int ex_value = expr->Eval();
        delete expr;
        expr = new expressions::number_expression(ex_value);
    }
    else
        expr->Eval();
}