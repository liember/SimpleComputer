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

void ConditionStatement::SetAddr(int a)
{
    asm_address = a;
}

int *ConditionStatement::GetAddr()
{
    return &asm_address;
}

int ConditionStatement::GetId()
{
    return address;
}

// TO DO MAKE IF STATEMNT WITH GO TO ONLY
std::vector<asmword *> *ConditionStatement::GenerateAsm(library::addressTable *variables, std::vector<parsing::AST::Statement *> *statements)
{
    std::vector<asmword *> *ret = new std::vector<asmword *>;

    asmword *prepare_command_load = new asmword(&asm_address, "LOAD", nullptr);
    asmword *prepare_command_sub = new asmword(&asm_address, "SUB", nullptr);
    asmword *compare_command = new asmword(&asm_address, "", statement->GetAddr());

    int *first_value_address = expr1->Requre(variables);
    int *second_value_address = expr2->Requre(variables);

    int *else_target = 0;

    switch (comparator)
    {
    case '<':
        prepare_command_load->operand = first_value_address;
        prepare_command_sub->operand = second_value_address;
        compare_command->name = "JNEG";
        break;

    case '>':
        prepare_command_load->operand = second_value_address;
        prepare_command_sub->operand = first_value_address;
        compare_command->name = "JNEG";
        break;

    case '=':
        prepare_command_load->operand = first_value_address;
        prepare_command_sub->operand = second_value_address;
        compare_command->name = "JZ";
        break;

    default:
        std::cout << "[ WARNING ] Undefined comparator in [ " << address << " ] IF [ expr ] <" << comparator << "> ...." << std::endl;
        break;
    }

    ret->push_back(prepare_command_load);
    ret->push_back(prepare_command_sub);
    ret->push_back(compare_command);

    std::vector<asmword *> *then_statement = statement->GenerateAsm(variables, statements);

    for (auto &&i : *then_statement)
    {
        ret->push_back(i);
    }

    return ret;
}