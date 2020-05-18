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

std::vector<asmword *> *expressions::binary_expression::GenerateAsm(library::addressTable *variables, library::value_heap *heap)
{
    std::vector<asmword *> *code = new std::vector<asmword *>;

    int *arg1_address, *arg2_address;

    if (expr1->GetType() == types::ConstExpression || expr1->GetType() == types::VariableExpression)
    {
        std::vector<asmword *> *sub_code;
        sub_code = expr1->GenerateAsm(variables, heap);

        for (auto &&i : *sub_code)
            code->push_back(i);
    }
    else
    {
        arg1_address = expr1->Requre(variables);
    }

    if (expr2->GetType() == types::ConstExpression || expr2->GetType() == types::VariableExpression)
    {
        std::vector<asmword *> *sub_code;
        sub_code = expr2->GenerateAsm(variables, heap);

        for (auto &&i : *sub_code)
            code->push_back(i);
    }
    else
    {
        arg2_address = expr2->Requre(variables);
    }

    if (expr2->GetType() == types::ConstExpression || expr2->GetType() == types::VariableExpression)
    {
        arg2_address = heap->Query();
    }
    if (expr1->GetType() == types::ConstExpression || expr1->GetType() == types::VariableExpression)
    {
        arg1_address = heap->Query();
    }

    asmword *load_cmd = new asmword(nullptr, "LOAD", arg1_address);
    asmword *operation_cmd = new asmword(nullptr, "", arg2_address);
    asmword *store_cmd = new asmword(nullptr, "STORE", heap->Push());

    code->push_back(load_cmd);
    code->push_back(operation_cmd);
    code->push_back(store_cmd);

    switch (operation)
    {
    case lexer::token::mul:
        operation_cmd->name = "MUL";
        break;
    case lexer::token::dif:
        operation_cmd->name = "SUB";
        break;
    case lexer::token::div:
        operation_cmd->name = "DIVIDE";
        break;
    case lexer::token::sum:
        operation_cmd->name = "ADD";
        break;
    default:
        break;
    }

    return code;
}