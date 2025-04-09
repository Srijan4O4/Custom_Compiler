
#ifndef PARSER_H
#define PARSER_H

#include "tokeniser.h"
#include "ast.h"
#include <vector>
#include <memory>
#include <string>

class Parser
{
public:
    std::vector<Token> tokens;
    size_t pos;
    Parser(const std::vector<Token> &toks);
    std::vector<std::shared_ptr<ASTNode>> parse();

private:
    Token current();
    std::string eat(const std::string &expectedType);
    std::shared_ptr<ASTNode> statement();
    std::shared_ptr<Expression> expression();
    std::shared_ptr<Expression> term();
    std::shared_ptr<Expression> factor();
};

#endif // PARSER_H
