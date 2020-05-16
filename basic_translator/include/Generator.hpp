#pragma once

#include <fstream>

#include "library.hpp"
#include "parser.hpp"

typedef library::addressTable variables;
typedef std::vector<parsing::AST::Statement *> statements;

class Generator
{
private:
    variables *vars;
    statements *states;

public:
    Generator(variables *v, statements *s);
    ~Generator();

    void Generate(std::string output_file_name);
};
