#include "composer.hpp"

composer::composer(std::vector<command *> *v)
{
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
}

void composer::Optimize()
{
    if (optimizations)
        for (auto &&i : *commands)
            i->EvalExpression();
}