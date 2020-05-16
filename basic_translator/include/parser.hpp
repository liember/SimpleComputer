#pragma once

#include "StringSwitch.hpp"

#include "lexer.hpp"
#include <string>
#include <vector>
#include <utility>
#include <sstream>
#include "AST.hpp"

#include "library.hpp"

namespace parsing
{
    class parser
    {
    private:
        std::vector<lexer::token::token> tokens;

        int pos;
        const unsigned int size;

        lexer::token::token Get(int relativePosition);
        bool Match(lexer::token::token_type type);

        AST::Statement *Statement(bool addrcheck = true);
        AST::expressions::expression *Expression();
        AST::expressions::expression *Additive();
        AST::expressions::expression *Multyplicative();
        AST::expressions::expression *Unary();
        AST::expressions::expression *Primary();

    public:
        explicit parser(std::vector<lexer::token::token> &toks);

        std::vector<AST::Statement *> Parse();
    };
} // namespace parsing