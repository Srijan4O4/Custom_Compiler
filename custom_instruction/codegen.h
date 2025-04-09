#ifndef CODEGEN_H
#define CODEGEN_H

#include "ast.h"
#include <string>
#include <vector>

class CodeGen
{
public:
    std::vector<std::string> instructions;
    void generate(std::shared_ptr<ASTNode> node);

private:
    std::string generate_expr(std::shared_ptr<Expression> expr);
    // Try to detect the pattern: log(x) + 2 * x
    bool match_logmuladd(std::shared_ptr<Expression> expr, std::string &var);
};

#endif // CODEGEN_H
