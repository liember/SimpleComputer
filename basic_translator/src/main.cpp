#include <iostream>
#include <string>
#include <fstream>

#include "lexer.hpp"
#include "parser.hpp"
#include "composer.hpp"
#include "Generator.hpp"

using namespace std;

int main(int argc, char **argv)
{

    // CONFIGURATION

    bool parsing_result_view = false;
    bool constant_expression_optimization = false;
    bool assembly_preview = false;
    bool values_info = false;

    if (argv[3] != nullptr)
    {
        std::string str(argv[3]);

        if (str.find('P') != std::string::npos)
            parsing_result_view = true;
        if (str.find('O') != std::string::npos)
            constant_expression_optimization = true;
        if (str.find('A') != std::string::npos)
            assembly_preview = true;
        if (str.find('V') != std::string::npos)
            values_info = true;
    }

    if (argv[1] == nullptr)
    {
        std::cout << "[ WARNING ] Please input [ inputfile ]\n";
        return 1;
    }

    std::string inp_filename(argv[1]);
    std::string out_filename;

    if (argv[2] == nullptr)
    {
        std::cout << "[ ATTENTION ] You dont input [ outputfile ]\n[ INFO ] The name will be generated automaticly\n";
        out_filename = inp_filename;
        auto mPos = out_filename.find('.');
        out_filename.replace(out_filename.begin() + mPos, out_filename.end(), ".sasm");
        std::cout << "[ INFO ] Has been generated output file name: [ " << out_filename << " ] \n\n";
    }
    else
    {
        out_filename = argv[2];
    }

    if (inp_filename.substr(inp_filename.find_last_of(".") + 1) != "sbas")
    {
        std::cout << "[ WARNING ] File is not [ .sbas ] extention " << inp_filename << std::endl;
        return 1;
    }

    std::ifstream in(inp_filename);

    if (!in.is_open())
    {
        cout << "[ WARNING ] File not found" << endl;
        return 1;
    }

    // ### CODE ###

    std::string line;
    vector<lexer::token::token> tokens;
    lexer::Tokinizer toker(tokens);

    while (getline(in, line)) // DONT TOUCH
        toker.Tokenize(line);
    tokens.push_back(lexer::token::token(lexer::token::token_type::Eof));
    in.close();

    parsing::parser p(tokens);
    std::vector<parsing::AST::Statement *> v = p.Parse();

    composer configurator(&v);
    configurator.CheckFails();

    if (constant_expression_optimization) // FLAG CONFIGUREABLE
        configurator.Optimize();

    configurator.GenerateVar();

    if (values_info) // FLAG CONFIGUREABLE
        configurator.PrintVariablesInfo();

    if (parsing_result_view) // FLAG CONFIGUREABLE
    {
        std::cout << std::endl;
        for (auto &&i : v)
            i->Print();
        std::cout << std::endl;
    }

    Generator code_gen(configurator.lib, &v);
    code_gen.PreGenerate();

    if (assembly_preview) // FLAG CONFIGUREABLE
        code_gen.Preview();

    code_gen.WriteToFile(out_filename);

    return 0;
}