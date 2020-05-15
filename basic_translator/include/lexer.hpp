#pragma once

#include "token.hpp"

#include <vector>
#include <ctype.h>

namespace lexer
{

    namespace // Keywords
    {
        inline constexpr char *Rem = (char *const) "REM";

        inline constexpr char *Input = (char *const) "INPUT";
        inline constexpr char *Output = (char *const) "OUTPUT";

        inline constexpr char *GoTo = (char *const) "GOTO";
        inline constexpr char *If = (char *const) "IF";
        inline constexpr char *Let = (char *const) "LET";

        inline constexpr char *End = (char *const) "END";

        inline constexpr char *Sum = (char *const) "+";
        inline constexpr char *Dif = (char *const) "-";
        inline constexpr char *Mul = (char *const) "*";
        inline constexpr char *Div = (char *const) "/";

        inline constexpr char *Less = (char *const) "<";
        inline constexpr char *More = (char *const) ">";
        inline constexpr char *Equal = (char *const) "==";

        inline constexpr char *Set = (char *const) "=";

        inline constexpr char *ExpEnd = (char *const) ")";
        inline constexpr char *ExpStart = (char *const) "(";
    } // namespace

    class Tokinizer
    {
    private:
        std::vector<token::token> &token_line;

    private:
        bool is_number(const std::string &s);
        void AddToken(token::token_type tok);
        void AddToken(token::token_type tok, std::string value);

    public:
        Tokinizer(std::vector<token::token> &list) : token_line(list) {}
        void Tokenize(std::string line);
    };
} // namespace lexer