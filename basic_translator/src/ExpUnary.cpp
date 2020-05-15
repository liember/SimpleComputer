#include "parser.hpp"

using namespace parsing::AST;

expressions::unary_expression::unary_expression(int op, expression *e1)
{
    expr = e1;
    operation = op;

    const int number_expr = expressions::types::ConstExpression;
    const int number_type = expressions::types::ConstValue;

    if (expr->GetType() != number_type || expr->GetType() != number_expr)
        expression_type = expressions::types::VariableExpression;
    else
        expression_type = expressions::types::ConstExpression;
}

expressions::unary_expression::~unary_expression()
{
    delete expr;
}

void expressions::unary_expression::Print()
{
    std::cout << " UnaryExpr ( ";
    expr->Print();
    std::cout << " Operation: ";
    switch (operation)
    {
    case lexer::token::sum:
        std::cout << "[+]";
        break;
    case lexer::token::dif:
        std::cout << "[-]";
        break;

    default:
        std::cout << "WARNING UNDEF OPERATION";
        break;
    }
    std::cout << " )";
}
int expressions::unary_expression::Eval()
{
    if (expression_type == expressions::types::ConstExpression)
    {
        const int ex_value = expr->Eval();
        delete expr;

        switch (operation)
        {
        case lexer::token::sum:
            expr = new number_expression(ex_value);
            return ex_value;
            break;
        case lexer::token::dif:
            expr = new number_expression(-ex_value);

            return -ex_value;
            break;
        }
    }
    else
    {
        expr->Eval();
    }
    std::cout << "undef unary operation" << std::endl;
    return INT32_MAX;
}

int expressions::unary_expression::GetType()
{
    return expression_type;
}

void expressions::unary_expression::RegValues()
{
    expr->RegValues();
}