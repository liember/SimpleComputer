#include "parser.hpp"

using namespace parsing;

lexer::token::token parser::Get(int relativePosition)
{
    int position = pos + relativePosition;
    if (position >= size)
        return tokens[tokens.size()];
    else
        return tokens[position];
}

bool parser::Match(lexer::token::token_type type)
{
    lexer::token::token current = Get(0);
    if (type != current.GetType())
        return false;
    else
    {
        pos++;
        return true;
    }
}

AST::expressions::expression *parser::Expression()
{
    return Additive();
    std::cout << std::endl;
}

AST::expressions::expression *parser::Additive()
{
    AST::expressions::expression *expr = Multyplicative();
    while (true)
    {
        if (Match(lexer::token::sum))
        {
            expr = new AST::expressions::binary_expression(lexer::token::sum, expr, Multyplicative());
            continue;
        }
        if (Match(lexer::token::dif))
        {
            expr = new AST::expressions::binary_expression(lexer::token::dif, expr, Multyplicative());
            continue;
        }
        break;
    }
    return expr;
}

AST::expressions::expression *parser::Multyplicative()
{
    AST::expressions::expression *expr = Primary();
    while (true)
    {
        if (Match(lexer::token::mul))
        {
            expr = new AST::expressions::binary_expression(lexer::token::mul, expr, Primary());
            continue;
        }
        if (Match(lexer::token::div))
        {
            expr = new AST::expressions::binary_expression(lexer::token::div, expr, Primary());
            continue;
        }
        break;
    }
    return expr;
}

AST::expressions::expression *parser::Primary()
{
    lexer::token::token cur_tok = Get(0);
    if (Match(lexer::token::token_type::Number))
    {
        return new AST::expressions::number_expression(std::stoi(cur_tok.GetValue()));
    }
    else if (Match(lexer::token::token_type::Exp_sta))
    {
        AST::expressions::expression *result = Expression();
        if (Match(lexer::token::token_type::Exp_end))
        {
            return result;
        }
        else
        {
            std::cout << "[ WARNING ] No end of custom priority expression ";
            exit(0);
        }
    }
    else if (Match(lexer::token::Query))
    {
        return new AST::expressions::variable_expression(*cur_tok.GetValue().c_str());
    }
    else
    {
        std::cout << "[ WARNING ] Unpredicted expression: Token("
                  << cur_tok.GetType() << ") Value(" << cur_tok.GetValue()
                  << ") " << std::endl;
        exit(0);
    }
}

parser::parser(std::vector<lexer::token::token> &toks) : tokens(toks),
                                                         size(tokens.size())
{
    pos = 0;
}

AST::Statement *parser::Statement(bool addrcheck)
{
    int address = INT32_MAX;
    lexer::token::token cur_tok = Get(0);
    if (addrcheck == true)
    {
        if (!Match(lexer::token::token_type::Number))
        {
            std::cout << "[ WARNING ] No address found" << std::endl, exit(0);
        }
        address = std::stoi(cur_tok.GetValue());
    }
    switch (Get(0).GetType())
    {
    case lexer::token::token_type::Input:
        pos++;
        if (Get(0).GetType() == lexer::token::token_type::Query)
        {
            return new AST::InputStatement(address, Expression());
        }
        else
        {
            std::cout << "[ WARNING ] Non variable input target: " << Get(0).GetType() << std::endl;
            exit(0);
        }

        break;
    case lexer::token::token_type::Output:
        pos++;
        return new AST::OutputStatement(address, Expression());
        break;
    case lexer::token::token_type::Goto:
        pos++;
        return new AST::GoToStatement(address, Expression());
        break;
    case lexer::token::token_type::If:
        pos++;
        return new AST::ConditionStatement(address,
                                           Expression(),
                                           (Match(lexer::token::token_type::Compare) ? *Get(-1).GetValue().c_str() : 'e'),
                                           Expression(),
                                           Statement(false));
        break;
    case lexer::token::token_type::Let:
        pos++;
        if (Get(0).GetType() == lexer::token::token_type::Query)
        {
            AST::expressions::expression *first = Expression();
            if (Match(lexer::token::token_type::Set))
            {
                return new AST::LetStatement(address, first, Expression());
            }
            else
                std::cout << "[ WARNING ] Equal statement not found", exit(0);
        }
        else
            std::cout << "[ WARNING ] Variable statement not found", exit(0);
        break;
    case lexer::token::token_type::End:
        pos++;
        return new AST::EndStatement(address);
        break;
    default:
        std::cout << "[ WARNING ] Unpredicted token type: " << Get(0).GetType() << std::endl;
        exit(0);
        break;
    }

    return nullptr;
}

std::vector<AST::Statement *> parser::Parse()
{
    std::vector<AST::Statement *> result;

    int previous_id = -1;

    while (!Match(lexer::token::token_type::Eof))
    {
        AST::Statement *current_statement = Statement(true);

        int current_id = current_statement->GetId();

        if (current_id <= previous_id)
        {
            std::cout << "[ WARNING ] Wrong addresation\n";
            std::cout << "[ ADDITIONAL WARNING INFO ] Previous: ";
            result[result.size() - 1]->Print();
            std::cout << "[ ADDITIONAL WARNING INFO ] Incorrect: ";
            current_statement->Print();
            exit(0);
        }

        result.push_back(current_statement);
        previous_id = current_id;
    }
    return result;
}
