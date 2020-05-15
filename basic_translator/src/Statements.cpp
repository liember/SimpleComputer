#include "parser.hpp"

using namespace parsing::AST;

InputStatement::InputStatement(int a, expressions::expression *e)
{
    address = a;
    var = e;
}

InputStatement::~InputStatement()
{
}

void InputStatement::Print()
{
    std::cout << "Address: [" << address << "] Ccommand: INPUT Variable: [" << var << "] " << std::endl;
}

void InputStatement::EvalExpression()
{
}

bool InputStatement::Analyze()
{
    if (var->GetType() != expressions::types::MutableValue)
    {
        std::cout << "[ WARNING ] Incorrect expression: \n[ Address: " << address << "] [ INPUT ] > CONSTANT VALUE <" << std::endl;
        return false;
    }
    return true;
}

void InputStatement::RegValues()
{
}

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
    std::cout << "Address: [" << address << "] Ccommand: OUTPUT Expression: ";
    expr->Print();
    std::cout << std::endl;
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
        std::cout << "[ ATTENTION ] Incorrect expression: \n\t\t[ Address: " << address << "] [ OUTPUT ] > IMUTABLE EXPRESSION <" << std::endl;
        return true;
    }

    if (expr->GetType() == var_expr)
    {
        std::cout << "[ WARNING ] Incorrect expression: \n[ Address: " << address << "] [ OUTPUT ] > MULTIPLE VARIABLES EXPRESSION <" << std::endl;
        return false;
    }

    return true;
}

void OutputStatement::RegValues()
{
}

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
    std::cout << "Address: [" << address << "] Ccommand: GOTO Expression: ";
    expr->Print();
    std::cout << std::endl;
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

void GoToStatement::RegValues()
{
}

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
    std::cout << "Address: [" << address << "] Ccommand: LET Expression: ";
    expr->Print();
    std::cout << std::endl;
}

void LetStatement::EvalExpression()
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

EndStatement::EndStatement(int a)
{
    address = a;
}

EndStatement::~EndStatement()
{
}

bool EndStatement::Analyze()
{
    return true;
}

void EndStatement::Print()
{
    std::cout << "Address: [" << address << "] Ccommand: END " << std::endl;
}

void EndStatement::EvalExpression()
{
}

void EndStatement::RegValues()
{
}

bool ConditionStatement::Analyze()
{
    const int number_type = expressions::types::ConstValue;
    const int var_type = expressions::types::MutableValue;

    if (expr1->GetType() != var_type && expr1->GetType() != number_type)
    {
        std::cout << "[ WARNING ] Incorrect expression: \n[ Address: " << address << "] [ IF ] > NOT VALUE < [ CMP ] [ VALUE ] [ OPERATION ]" << std::endl;
        std::cout << " \t\t Expression has a type:" << expr1->GetType() << std::endl;
        return false;
    }

    if (expr2->GetType() != var_type && expr2->GetType() != number_type)
    {
        std::cout << "[ WARNING ] Incorrect expression: \n[ Address: " << address << "] [ IF ] [ VALUE ] [ CMP ]  > NOT VALUE < [ OPERATION ]" << std::endl;
        return false;
    }

    return true;
}

ConditionStatement::ConditionStatement(int addr, expressions::expression *e1, char cmp, expressions::expression *e2, Statement *st)
{
    address = addr;
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
    std::cout << "Address: [" << address << "] Ccommand: IF Expression: [ ";
    expr1->Print();
    std::cout << "] [ " << comparator << " ] Expression [ ";
    expr2->Print();
    std::cout << "]" << std::endl
              << "\tThen ";
    statement->Print();
}

void ConditionStatement::EvalExpression()
{
    if (expr1->GetType() == expressions::types::ConstExpression)
    {
        const int ex_value = expr1->Eval();

        delete expr1;

        expr1 = new expressions::number_expression(ex_value);
        expr1->Eval();
    }
    else
    {
        expr1->Eval();
    }

    if (expr2->GetType() == expressions::types::ConstExpression)
    {
        const int ex_value = expr2->Eval();

        delete expr2;

        expr2 = new expressions::number_expression(ex_value);
        expr2->Eval();
    }
    else
    {
        expr2->Eval();
    }
}

void ConditionStatement::RegValues()
{
}