#include "composer.hpp"

composer::composer(std::vector<command *> *v)
{
    lib = new library::addressTable();
    commands = v;
}

composer::~composer()
{
}

void composer::CheckFails()
{
    for (auto &&i : *commands)
    {
        if (!i->Analyze())
            exit(0);
    }
    std::cout << std::endl;
}

void composer::Optimize()
{
    for (auto &&i : *commands)
        i->EvalExpression();
}

void composer::GenerateVar()
{
    for (auto &&i : *commands)
        i->RegValues(lib);
    for (auto &&i : lib->values)
        commands->insert(commands->begin(), ValueToCmd(i.second));
}

command *composer::ValueToCmd(library::value *val)
{
    const int unused_addres = INT32_MAX;
    return new parsing::AST::SetStatement(unused_addres, val->val, val->GetAddr());
}

void composer::PrintVariablesInfo()
{
    lib->Print();
}