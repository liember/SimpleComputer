#include <iostream>
#include <string>
#include <fstream>

#include "lexer.hpp"
#include "parser.hpp"
#include "composer.hpp"

using namespace std;

int main(int argc, char **argv)
{
    std::ifstream in("test.bas");

    if (!in.is_open())
    {
        cout << "[!] File not found" << endl;
        return 1;
    }

    std::string line;
    vector<lexer::token::token> tokens;
    lexer::Tokinizer toker(tokens);

    while (getline(in, line))
        toker.Tokenize(line);
    tokens.push_back(lexer::token::token(lexer::token::token_type::Eof));
    in.close();

    parsing::parser p(tokens);
    std::vector<parsing::AST::Statement *> v = p.Parse();

    composer configurator(&v);

    configurator.CheckFails();
    configurator.Optimize();
    configurator.GenerateVarCommands();

    std::cout << std::endl;
    std::cout << std::endl;

    for (auto &&i : v)
        i->Print();
    std::cout << std::endl;

    return 0;
}