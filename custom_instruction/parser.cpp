#include "parser.h"
#include <stdexcept>

Parser::Parser(const std::vector<Token> &toks) : tokens(toks), pos(0) {}

Token Parser::current()
{
    if (pos < tokens.size())
        return tokens[pos];
    return {"EOF", ""};
}

std::string Parser::eat(const std::string &expectedType)
{
    Token tok = current();
    if (tok.first == expectedType)
    {
        pos++;
        return tok.second;
    }
    else
    {
        throw std::runtime_error("Expected " + expectedType + " but got " + tok.first);
    }
}

std::vector<std::shared_ptr<ASTNode>> Parser::parse()
{
    std::vector<std::shared_ptr<ASTNode>> statements;
    while (current().first != "EOF")
    {
        statements.push_back(statement());
    }
    return statements;
}

std::shared_ptr<ASTNode> Parser::statement()
{
    Token tok = current();
    if (tok.first == "INT")
    {
        eat("INT");
        std::string varName = eat("ID");
        eat("ASSIGN");
        auto expr = expression();
        eat("SEMICOLON");
        return std::make_shared<Assignment>(varName, expr);
    }
    else if (tok.first == "PRINT")
    {
        eat("PRINT");
        eat("LPAREN");
        auto expr = expression();
        eat("RPAREN");
        eat("SEMICOLON");
        return std::make_shared<Print>(expr);
    }
    else
    {
        throw std::runtime_error("Unexpected statement start: " + tok.first);
    }
}

std::shared_ptr<Expression> Parser::expression()
{
    auto node = term();
    while (current().first == "ADD")
    {
        std::string op = eat("ADD");
        node = std::make_shared<BinOp>(node, op, term());
    }
    return node;
}

std::shared_ptr<Expression> Parser::term()
{
    auto node = factor();
    while (current().first == "MUL")
    {
        std::string op = eat("MUL");
        node = std::make_shared<BinOp>(node, op, factor());
    }
    return node;
}

std::shared_ptr<Expression> Parser::factor()
{
    Token tok = current();
    if (tok.first == "NUMBER")
    {
        std::string num = eat("NUMBER");
        return std::make_shared<Number>(std::stod(num));
    }
    else if (tok.first == "ID")
    {
        std::string id = eat("ID");
        // Check for a function call when an LPAREN follows.
        if (current().first == "LPAREN")
        {
            eat("LPAREN");
            std::vector<std::shared_ptr<Expression>> args;
            args.push_back(expression());
            eat("RPAREN");
            return std::make_shared<FunctionCall>(id, args);
        }
        return std::make_shared<Variable>(id);
    }
    else if (tok.first == "LPAREN")
    {
        eat("LPAREN");
        auto expr = expression();
        eat("RPAREN");
        return expr;
    }
    else
    {
        throw std::runtime_error("Unexpected token in factor: " + tok.first);
    }
}
    