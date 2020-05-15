#include "lexer.hpp"
#include "StringSwitch.hpp"

#include <sstream>

using namespace lexer;

bool Tokinizer::is_number(const std::string &s)
{
    std::string::const_iterator it;
    if (s[0] != '-')
        it = s.begin();
    else
        it = s.begin() + 1;
    while (it != s.end() && std::isdigit(*it))
        ++it;
    return !s.empty() && it == s.end();
}

void Tokinizer::AddToken(token::token_type tok)
{
    token::token t(tok);
    token_line.push_back(t);
}

void Tokinizer::AddToken(token::token_type tok, std::string value)
{
    token::token t(tok, value);
    token_line.push_back(t);
}

void Tokinizer::Tokenize(std::string line)
{
    std::stringstream ss(line);
    std::string word;

    bool skipflag = true;

    while (ss >> word && skipflag)
    {
        ss_switch(word)
        {
            ss_case(Rem) : skipflag = false;
            token_line.pop_back();
            break;

            ss_case(Input) : AddToken(token::Input);
            break;

            ss_case(Output) : AddToken(token::Output);
            break;

            ss_case(GoTo) : AddToken(token::Goto);
            break;

            ss_case(If) : AddToken(token::If);
            break;

            ss_case(Let) : AddToken(token::Let);
            break;

            ss_case(End) : AddToken(token::End);
            break;

            ss_case(Sum) : AddToken(token::sum, word);
            break;

            ss_case(Dif) : AddToken(token::dif, word);
            break;

            ss_case(Mul) : AddToken(token::mul, word);
            break;

            ss_case(Div) : AddToken(token::div, word);
            break;

            ss_case(Less) : AddToken(token::Compare, word);
            break;

            ss_case(More) : AddToken(token::Compare, word);
            break;

            ss_case(Equal) : AddToken(token::Compare, word);
            break;

            ss_case(Set) : AddToken(token::Set);
            break;

            ss_case(ExpEnd) : AddToken(token::Exp_end);
            break;

            ss_case(ExpStart) : AddToken(token::Exp_sta);
            break;

        ss_default:
            if (is_number(word))
            {
                AddToken(token::Number, word);
            }
            else
            {
                AddToken(token::Query, word);
            }

            break;
        }
    }
}