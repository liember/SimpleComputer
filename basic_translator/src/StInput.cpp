#include "parser.hpp"

using namespace parsing::AST;

InputStatement::InputStatement(int a, expressions::expression *e) : address(a)
{
    var = e;
}

InputStatement::~InputStatement()
{
}

void InputStatement::Print()
{
    std::cout << "[ " << address << " ] [ INPUT ] [ ";
    var->Print();
    std::cout << "] " << std::endl;
}

void InputStatement::EvalExpression()
{
}

bool InputStatement::Analyze()
{
    if (var->GetType() != expressions::types::MutableValue)
    {
        std::cout << "[ WARNING ] Incorrect expression: \n[ Address: " << address << "] [ INPUT ] < CONSTANT VALUE >" << std::endl;
        return false;
    }
    return true;
}

void InputStatement::RegValues(library::addressTable *lib)
{
    var->RegValues(lib);
}

void InputStatement::SetAddr(int a)
{
    asm_address = a;
}

int *InputStatement::GetAddr()
{
    return &asm_address;
}

int InputStatement::GetId()
{
    return address;
}

std::vector<asmword *> *InputStatement::GenerateAsm(library::addressTable *variables, std::vector<parsing::AST::Statement *> *statements)
{
    std::vector<asmword *> *ret = new std::vector<asmword *>;
    int *input_variable_addr = var->Requre(variables);

    asmword *command = new asmword(&asm_address, "READ", input_variable_addr);
    ret->push_back(command);

    return ret;
}