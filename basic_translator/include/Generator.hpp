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

    int current_asm_addr;
    int asm_code_size;

public:
    Generator(variables *v, statements *s);
    ~Generator();

    void PreGenerate();
    void Generate(std::string output_file_name);
};
