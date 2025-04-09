#include "codegen.h"
#include <sstream>

void CodeGen::generate(std::shared_ptr<ASTNode> node)
{
    // For assignments and print statements.
    if (auto assign = std::dynamic_pointer_cast<Assignment>(node))
    {
        std::string var;
        if (match_logmuladd(assign->expr, var))
        {
            instructions.push_back("LOGMULADD " + assign->varName + ", " + var);
        }
        else
        {
            std::string exprCode = generate_expr(assign->expr);
            instructions.push_back("MOV " + assign->varName + ", " + exprCode);
        }
    }
    else if (auto pr = std::dynamic_pointer_cast<Print>(node))
    {
        std::string exprCode = generate_expr(pr->expr);
        instructions.push_back("PRINT " + exprCode);
    }
}

std::string CodeGen::generate_expr(std::shared_ptr<Expression> expr)
{
    if (auto num = std::dynamic_pointer_cast<Number>(expr))
    {
        return std::to_string(num->value);
    }
    else if (auto var = std::dynamic_pointer_cast<Variable>(expr))
    {
        return var->name;
    }
    else if (auto bin = std::dynamic_pointer_cast<BinOp>(expr))
    {
        std::string left = generate_expr(bin->left);
        std::string right = generate_expr(bin->right);
        return "(" + left + " " + bin->op + " " + right + ")";
    }
    else if (auto func = std::dynamic_pointer_cast<FunctionCall>(expr))
    {
        std::string arg = generate_expr(func->args[0]);
        return func->funcName + "(" + arg + ")";
    }
    return "";
}

bool CodeGen::match_logmuladd(std::shared_ptr<Expression> expr, std::string &var)
{
    // Check if expr is a binary addition.
    auto bin = std::dynamic_pointer_cast<BinOp>(expr);
    if (bin && bin->op == "+")
    {
        // Left should be a function call: log(x)
        auto func = std::dynamic_pointer_cast<FunctionCall>(bin->left);
        if (func && func->funcName == "log" && func->args.size() == 1)
        {
            // Right should be a multiplication: 2 * x
            auto binMul = std::dynamic_pointer_cast<BinOp>(bin->right);
            if (binMul && binMul->op == "*")
            {
                auto num = std::dynamic_pointer_cast<Number>(binMul->left);
                auto varNode = std::dynamic_pointer_cast<Variable>(binMul->right);
                if (num && varNode && num->value == 2)
                {
                    var = varNode->name;
                    return true;
                }
            }
        }
    }
    return false;
}
