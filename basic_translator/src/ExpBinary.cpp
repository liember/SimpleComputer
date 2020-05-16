#include "parser.hpp"

using namespace parsing::AST;

expressions::binary_expression::binary_expression(int op, expressions::expression *e1, expressions::expression *e2)
{
    expr1 = e1;
    expr2 = e2;
    operation = op;

    const int number_expr = expressions::types::ConstExpression;
    const int number_type = expressions::types::ConstValue;

    if ((expr1->GetType() == number_expr || expr1->GetType() == number_type) && (expr2->GetType() == number_type || expr2->GetType() == number_expr))
        expression_type = expressions::types::ConstExpression;
    else
        expression_type = expressions::types::VariableExpression;
}

expressions::binary_expression::~binary_expression()
{
    delete expr1;
    delete expr2;
}

int expressions::binary_expression::Eval()
{
    const int number_expr = expressions::types::ConstExpression;
    const int number_type = expressions::types::ConstValue;

    if (expression_type == number_expr || expression_type == number_type)
    {
        const int ex1_value = expr1->Eval();
        const int ex2_value = expr2->Eval();

        delete expr1;
        delete expr2;

        expr1 = new number_expression(ex1_value);
        expr2 = new number_expression(ex2_value);

        switch (operation)
        {
        case lexer::token::sum:
            return expr1->Eval() + expr2->Eval();
            break;
        case lexer::token::dif:
            return expr1->Eval() - expr2->Eval();
            break;
        case lexer::token::mul:
            return expr1->Eval() * expr2->Eval();
            break;
        case lexer::token::div:
        default:
            return expr1->Eval() / expr2->Eval();
            break;
        }
    }
    else
    {
        if (expr1->GetType() == number_expr || expr1->GetType() == number_type)
        {
            const int ex1_value = expr1->Eval();

            delete expr1;

            expr1 = new number_expression(ex1_value);
            expr2->Eval();
        }
        if (expr2->GetType() == number_expr || expr2->GetType() == number_type)
        {
            const int ex2_value = expr2->Eval();

            delete expr2;

            expr2 = new number_expression(ex2_value);
            expr1->Eval();
        }
        return 0;
    }

    std::cout << "undef match operation" << std::endl;
    exit(0);
    return 0;
}

int expressions::binary_expression::GetType()
{
    return expression_type;
}

void expressions::binary_expression::Print()
{
    std::cout << "Op( ";
    expr1->Print();
    switch (operation)
    {
    case lexer::token::sum:
        std::cout << "[+] ";
        break;
    case lexer::token::dif:
        std::cout << "[-] ";
        break;
    case lexer::token::div:
        std::cout << "[/] ";
        break;
    case lexer::token::mul:
        std::cout << "[*] ";
        break;

    default:
        std::cout << "WARNING UNDEF OPERATION";
        break;
    }
    expr2->Print();
    std::cout << ") ";
}

void expressions::binary_expression::RegValues(library::addressTable *lib)
{
    expr1->RegValues(lib);
    expr2->RegValues(lib);
}

int *expressions::binary_expression::Requre(library::addressTable *lib)
{
    std::cout << "[ CRITICAL WARNING ] This code should never have been run [ binary_expression::Requre() ]" << std::endl;
    return nullptr;
}