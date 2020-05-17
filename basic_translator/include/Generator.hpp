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

    std::vector<asmword *> command_list;

    int current_asm_addr;

public:
    Generator(variables *v, statements *s);
    ~Generator();

    void Preview();

    void PreGenerate();
    void Generate(std::string output_file_name);
};
