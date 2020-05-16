#include "parser.hpp"

using namespace parsing::AST;

LetStatement::LetStatement(int addr, expressions::expression *e1, expressions::expression *e2) : address(addr)
{
    expr1 = e1;
    expr2 = e2;
}

bool LetStatement::Analyze()
{
    const int var = expressions::types::MutableValue;

    if (expr1->GetType() != var)
    {
        std::cout << "[ WARNING ] Incorrect expression: \n[ Address: " << address << "] [ LET ] < IS NOT VARIABLE > [ = ] [ Expression ]" << std::endl;
        std::cout << "\t\t Is it [";
        expr1->Print();
        std::cout << std::endl;
        return false;
    }

    return true;
}

LetStatement::~LetStatement()
{
    delete expr1;
    delete expr2;
}

void LetStatement::RegValues(library::addressTable *lib)
{
    expr1->RegValues(lib);
    expr2->RegValues(lib);
}

void LetStatement::Print()
{
    std::cout << "[ " << address << " ] [ LET ] [ ";
    expr1->Print();
    std::cout << "] [ = ] [";
    expr2->Print();
    std::cout << "] " << std::endl;
}

void LetStatement::EvalExpression()
{
    if (expr2->GetType() == expressions::types::ConstExpression)
    {
        const int ex_value = expr2->Eval();
        delete expr2;
        expr2 = new expressions::number_expression(ex_value);
    }
    else
        expr2->Eval();
}

void LetStatement::SetAddr(int a)
{
    asm_address = a;
}

int *LetStatement::GetAddr()
{
    return &asm_address;
}

int LetStatement::GetId()
{
    return address;
}

std::vector<asmword *> *LetStatement::GenerateAsm(library::addressTable *variables, std::vector<parsing::AST::Statement *> *statements)
{
    return nullptr;
}