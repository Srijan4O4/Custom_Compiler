#include "interpreter.h"
#include <iostream>
#include <cmath>
#include <stdexcept>

// Helper: evaluate an expression (used by visitor functions)
double evalExpression(ASTNode *node, Interpreter &interp);

double evalExpression(ASTNode *node, Interpreter &interp)
{
    if (auto num = dynamic_cast<Number *>(node))
    {
        return num->value;
    }
    else if (auto var = dynamic_cast<Variable *>(node))
    {
        if (interp.env.find(var->name) != interp.env.end())
            return interp.env[var->name];
        else
            throw std::runtime_error("Undefined variable: " + var->name);
    }
    else if (auto bin = dynamic_cast<BinOp *>(node))
    {
        double left = evalExpression(bin->left.get(), interp);
        double right = evalExpression(bin->right.get(), interp);
        if (bin->op == "+")
            return left + right;
        if (bin->op == "*")
            return left * right;
        throw std::runtime_error("Unsupported operator: " + bin->op);
    }
    else if (auto func = dynamic_cast<FunctionCall *>(node))
    {
        if (func->funcName == "log")
        {
            double arg = evalExpression(func->args[0].get(), interp);
            return std::log(arg);
        }
    }
    return 0;
}

void Interpreter::visit(Assignment *assign)
{
    double value = evalExpression(assign->expr.get(), *this);
    env[assign->varName] = value;
}

void Interpreter::visit(Print *printStmt)
{
    double value = evalExpression(printStmt->expr.get(), *this);
    std::cout << value << std::endl;
}

// The accept methods for AST nodes call these visitor functions.
void Number::accept(Interpreter &interp)
{
    interp.visit(this);
}
void Variable::accept(Interpreter &interp)
{
    interp.visit(this);
}
void BinOp::accept(Interpreter &interp)
{
    interp.visit(this);
}
void FunctionCall::accept(Interpreter &interp)
{
    interp.visit(this);
}
void Assignment::accept(Interpreter &interp)
{
    interp.visit(this);
}
void Print::accept(Interpreter &interp)
{
    interp.visit(this);
}

// Dummy implementations for unused visitor methods:
void Interpreter::visit(Number *num) { /* No action needed */ }
void Interpreter::visit(Variable *var) { /* No action needed */ }
void Interpreter::visit(BinOp *bin) { /* No action needed here; evaluation done in evalExpression */ }
void Interpreter::visit(FunctionCall *func) { /* No action needed here */ }
