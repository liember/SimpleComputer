#pragma once

#include <iostream>
#include <string>
#include <vector>

namespace lexer
{

    namespace token
    {
        enum token_type
        {
            Input,
            Output,
            Goto,
            If,
            Let,
            End,

            Set,

            Compare,

            // internal commands
            Exp_end,
            Exp_sta,

            Rem,

            mul,
            dif,
            div,
            sum,

            Query,
            Number,

            Eof
        };

        class token
        {
        private:
            const int token_type;
            const std::string token_value;

        public:
            explicit token(int token, std::string val = "") : token_type(token), token_value(val) {}
            std::string GetValue() { return token_value; }
            int GetType() { return token_type; }
        };
    } // namespace token
} // namespace lexer