#include "parser.hpp"

using namespace parsing::AST;

GoToStatement::GoToStatement(int a, expressions::expression *e)
{
    address = a;
    expr = e;
}

GoToStatement::~GoToStatement()
{
    delete expr;
}
void GoToStatement::Print()
{
    std::cout << "[ " << address << " ] [ GOTO ] [ ";
    expr->Print();
    std::cout << "] " << std::endl;
}

bool GoToStatement::Analyze()
{
    const int number_expr = expressions::types::ConstExpression;
    const int number_type = expressions::types::ConstValue;

    if (expr->GetType() != number_expr && expr->GetType() != number_type)
    {
        std::cout << "[ WARNING ] Incorrect expression: \n[ Address: " << address << "] [ GOTO ] > IS NOT CONSTANT EXPRESSION <" << std::endl;
        return false;
    }

    return true;
}

void GoToStatement::EvalExpression()
{
    const int ex_value = expr->Eval();
    delete expr;
    expr = new expressions::number_expression(ex_value);
}

void GoToStatement::RegValues(library::addressTable *lib)
{
}