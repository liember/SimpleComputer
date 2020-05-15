#include "parser.hpp"

using namespace parsing::AST;

OutputStatement::OutputStatement(int a, expressions::expression *e)
{
    address = a;
    expr = e;
}

OutputStatement::~OutputStatement()
{
    delete expr;
}
void OutputStatement::Print()
{
    std::cout << "[ " << address << " ] [ OUTPUT ] [ ";
    expr->Print();
    std::cout << "] " << std::endl;
}

void OutputStatement::EvalExpression()
{
    if (expr->GetType() == expressions::types::ConstExpression)
    {
        const int ex_value = expr->Eval();

        delete expr;

        expr = new expressions::number_expression(ex_value);
        expr->Eval();
    }
    else
    {
        expr->Eval();
    }
}

bool OutputStatement::Analyze()
{

    const int number_expr = expressions::types::ConstExpression;
    const int number_type = expressions::types::ConstValue;

    const int var_expr = expressions::types::VariableExpression;

    if (expr->GetType() == number_expr || expr->GetType() == number_type)
    {
        std::cout << "[ ATTENTION ] Suspicious expression: " << std::endl;
        std::cout << "\t\t [Address:" << address << "][OUTPUT]<IMUTABLE EXPRESSION> " << std::endl;
        std::cout << "\t\t ";
        expr->Print();
        return true;
    }

    if (expr->GetType() == var_expr)
    {
        std::cout << "[ WARNING ] Incorrect expression: \n[ Address: " << address << "] [ OUTPUT ] < MULTIPLE VARIABLES EXPRESSION >" << std::endl;
        return false;
    }

    return true;
}

void OutputStatement::RegValues()
{
}