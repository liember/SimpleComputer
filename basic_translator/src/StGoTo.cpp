#include "parser.hpp"

using namespace parsing::AST;

GoToStatement::GoToStatement(int a, expressions::expression *e) : address(a)
{
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

void GoToStatement::SetAddr(int a)
{
    asm_address = a;
}

int *GoToStatement::GetAddr()
{
    return &asm_address;
}

int GoToStatement::GetId()
{
    return address;
}

std::vector<asmword *> *GoToStatement::GenerateAsm(library::addressTable *variables, std::vector<parsing::AST::Statement *> *statements)
{
    std::vector<asmword *> *ret = new std::vector<asmword *>;

    const int required_id = expr->Eval();
    int *jump_target;

    for (auto &&i : *statements)
    {
        if (i->GetId() == required_id)
            jump_target = i->GetAddr();
    }
    asmword *command = new asmword(&asm_address, "HALT", nullptr);
    ret->push_back(command);
    return ret;
}
