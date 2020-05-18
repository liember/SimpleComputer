#pragma once

#include "vector"
#include "parser.hpp"
#include "library.hpp"

typedef parsing::AST::Statement command;

class composer
{
private:
    std::vector<command *> *commands;
    command *ValueToCmd(library::value *val);

public:
    library::addressTable *lib;

    explicit composer(std::vector<command *> *v);

    void CheckFails();
    void Optimize();

    void GenerateVar();

    void PrintVariablesInfo();

    ~composer();
};
