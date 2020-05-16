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

                virtual void RegValues(library::addressTable *lib) = 0;
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

                void RegValues(library::addressTable *lib) override;
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

                void RegValues(library::addressTable *lib) override;
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

                void RegValues(library::addressTable *lib) override;
            };
        } // namespace expressions

        class Statement // interface
        {
        private:
        public:
            virtual ~Statement() {}
            virtual void Print() = 0;
            virtual void EvalExpression() = 0;

            virtual void RegValues(library::addressTable *lib) = 0;
            virtual bool Analyze() = 0;
        };

        class InputStatement : public Statement
        {
        private:
            const int address;

            expressions::expression *var;

        public:
            InputStatement(int a, expressions::expression *v);
            ~InputStatement() override;
            void EvalExpression() override;
            void Print() override;

            void RegValues(library::addressTable *lib) override;
            bool Analyze() override;
        };

        class OutputStatement : public Statement
        {
        private:
            const int address;

            expressions::expression *expr;

        public:
            OutputStatement(int a, expressions::expression *e);
            ~OutputStatement() override;
            void EvalExpression() override;
            void Print() override;

            void RegValues(library::addressTable *lib) override;
            bool Analyze() override;
        };

        class GoToStatement : public Statement
        {
        private:
            const int address;

            expressions::expression *expr;

        public:
            GoToStatement(int a, expressions::expression *e);
            ~GoToStatement() override;
            void EvalExpression() override;
            void Print() override;

            void RegValues(library::addressTable *lib) override;
            bool Analyze() override;
        };

        class ConditionStatement : public Statement
        {
        private:
            const int address;

            char comparator;

            expressions::expression *expr1;
            expressions::expression *expr2;
            Statement *statement;

        public:
            ConditionStatement(int addr, expressions::expression *e1, char cmp, expressions::expression *e2, Statement *st);
            ~ConditionStatement() override;
            void EvalExpression() override;
            void Print() override;

            void RegValues(library::addressTable *lib) override;
            bool Analyze() override;
        };

        class LetStatement : public Statement
        {
        private:
            const int address;

            expressions::expression *expr1;
            expressions::expression *expr2;

        public:
            LetStatement(int addr, expressions::expression *e1, expressions::expression *e2);
            ~LetStatement() override;
            void EvalExpression() override;
            void Print() override;

            void RegValues(library::addressTable *lib) override;
            bool Analyze() override;
        };

        class EndStatement : public Statement
        {
        private:
            const int address;

        public:
            EndStatement(int addr);
            ~EndStatement() override;
            void EvalExpression() override;
            void Print() override;

            void RegValues(library::addressTable *lib) override;
            bool Analyze() override;
        };

        class SetStatement : public Statement
        {
        private:
            const int address;

            int value;

        public:
            SetStatement(int addr, int val);
            ~SetStatement() override;
            void EvalExpression() override;
            void Print() override;

            void RegValues(library::addressTable *lib) override;
            bool Analyze() override;
        };

    } // namespace AST

} // namespace parsing