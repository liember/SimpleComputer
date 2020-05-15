#pragma once

#include "StringSwitch.hpp"

#include "lexer.hpp"
#include <string>
#include <vector>
#include <utility>
#include <sstream>

#include "library.hpp"

namespace parsing
{

    namespace AST
    {
        namespace expressions
        {
            enum types
            {
                ConstExpression,
                VariableExpression,
                ConstValue,
                MutableValue
            };

            class expression // interface
            {
            private:
            public:
                virtual void Print() = 0;
                virtual int Eval() = 0;
                virtual int GetType() = 0;
                virtual ~expression() {}

                virtual void RegValues() = 0;
            };

            class variable_expression : public expression
            {
            private:
                const char value;

            public:
                variable_expression(char val);
                ~variable_expression() override;
                void Print() override;
                int Eval() override;
                int GetType() override;

                void RegValues() override;
            };

            class number_expression : public expression
            {
            private:
                const int value;

            public:
                number_expression(int val);
                ~number_expression() override;
                void Print() override;
                int Eval() override;
                int GetType() override;

                void RegValues() override;
            };

            class binary_expression : public expression
            {
            private:
                expression *expr1;
                expression *expr2;

                int expression_type;
                int operation;

            public:
                binary_expression(int op, expression *e1, expression *e2);
                ~binary_expression() override;
                void Print() override;
                int Eval() override;
                int GetType() override;

                void RegValues() override;
            };
        } // namespace expressions

        class Statement // interface
        {
        private:
        public:
            virtual ~Statement() {}
            virtual void Print() = 0;
            virtual void EvalExpression() = 0;

            virtual void RegValues() = 0;
            virtual bool Analyze() = 0;
        };

        class InputStatement : public Statement
        {
        private:
            int address;
            expressions::expression *var;

        public:
            InputStatement(int a, expressions::expression *v);
            ~InputStatement() override;
            void EvalExpression() override;
            void Print() override;

            void RegValues() override;
            bool Analyze() override;
        };

        class OutputStatement : public Statement
        {
        private:
            int address;
            expressions::expression *expr;

        public:
            OutputStatement(int a, expressions::expression *e);
            ~OutputStatement() override;
            void EvalExpression() override;
            void Print() override;

            void RegValues() override;
            bool Analyze() override;
        };

        class GoToStatement : public Statement
        {
        private:
            int address;
            expressions::expression *expr;

        public:
            GoToStatement(int a, expressions::expression *e);
            ~GoToStatement() override;
            void EvalExpression() override;
            void Print() override;

            void RegValues() override;
            bool Analyze() override;
        };

        class ConditionStatement : public Statement
        {
        private:
            int address;
            char comparator;

            expressions::expression *expr1;
            expressions::expression *expr2;
            Statement *statement;

        public:
            ConditionStatement(int addr, expressions::expression *e1, char cmp, expressions::expression *e2, Statement *st);
            ~ConditionStatement() override;
            void EvalExpression() override;
            void Print() override;

            void RegValues() override;
            bool Analyze() override;
        };

        class LetStatement : public Statement
        {
        private:
            int address;
            expressions::expression *expr;

        public:
            LetStatement(int addr, expressions::expression *e);
            ~LetStatement() override;
            void EvalExpression() override;
            void Print() override;

            void RegValues() override;
            bool Analyze() override;
        };

        class EndStatement : public Statement
        {
        private:
            int address;

        public:
            EndStatement(int addr);
            ~EndStatement() override;
            void EvalExpression() override;
            void Print() override;

            void RegValues() override;
            bool Analyze() override;
        };

    } // namespace AST

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