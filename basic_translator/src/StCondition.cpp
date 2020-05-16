#include "parser.hpp"

using namespace parsing::AST;

ConditionStatement::ConditionStatement(int addr, expressions::expression *e1, char cmp, expressions::expression *e2, Statement *st) : address(addr)
{
    comparator = cmp;
    expr1 = e1;
    expr2 = e2;
    statement = st;
}

ConditionStatement::~ConditionStatement()
{
    delete statement;
    delete expr1;
    delete expr2;
}

void ConditionStatement::Print()
{
    std::cout << "[ " << address << " ] [ IF ] [ ";
    expr1->Print();
    std::cout << "] [ " << comparator << " ] [ ";
    expr2->Print();
    std::cout << "] " << std::endl
              << "\t [ Then ] ";
    statement->Print();
}

bool ConditionStatement::Analyze()
{
    const int number_type = expressions::types::ConstValue;
    const int var_type = expressions::types::MutableValue;

    if (expr1->GetType() != var_type && expr1->GetType() != number_type)
    {
        std::cout << "[ WARNING ] Incorrect expression: \n[ Address: " << address << "] [ IF ] < NOT VALUE > [ CMP ] [ VALUE ] [ OPERATION ]" << std::endl;
        std::cout << " \t\t Expression has a type:" << expr1->GetType() << std::endl;
        return false;
    }

    if (expr2->GetType() != var_type && expr2->GetType() != number_type)
    {
        std::cout << "[ WARNING ] Incorrect expression: \n[ Address: " << address << "] [ IF ] [ VALUE ] [ CMP ]  < NOT VALUE > [ OPERATION ]" << std::endl;
        return false;
    }

    return true;
}

void ConditionStatement::EvalExpression()
{
}

void ConditionStatement::RegValues(library::addressTable *lib)
{
    expr1->RegValues(lib);
    expr2->RegValues(lib);
}