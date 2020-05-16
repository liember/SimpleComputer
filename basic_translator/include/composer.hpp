#pragma once

#include "vector"
#include "parser.hpp"
#include "library.hpp"

typedef parsing::AST::Statement command;

class composer
{
private:
    library::addressTable *lib;
    std::vector<command *> *commands;

    command *ValueToCmd(library::value *val);

public:
    explicit composer(std::vector<command *> *v);

    void CheckFails();
    void Optimize();

    void GenerateVar();

    ~composer();
};
