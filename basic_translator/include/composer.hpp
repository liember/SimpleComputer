#pragma once

#include "vector"
#include "parser.hpp"
#include "library.hpp"

typedef parsing::AST::Statement command;

class composer
{
private:
    bool optimizations = false;
    bool analize = true;

    std::vector<command *> *commands;

    library::addressTable value_table;

public:
    explicit composer(std::vector<command *> *v);

    void CheckFails();
    void Optimize();

    ~composer();
};
