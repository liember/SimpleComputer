#pragma once

#include "vector"
#include "parser.hpp"
#include "library.hpp"

typedef parsing::AST::Statement command;

class composer
{
private:
    std::vector<command *> *commands;

public:
    explicit composer(std::vector<command *> *v);

    void CheckFails();
    void Optimize();

    ~composer();
};
