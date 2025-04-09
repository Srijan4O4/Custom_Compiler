#ifndef AST_H
#define AST_H

#include <string>
#include <memory>
#include <sstream>
#include <vector>

class Interpreter;

class ASTNode
{
public:
    virtual std::string toString() = 0;
    virtual void accept(Interpreter &interp) = 0;
    virtual ~ASTNode() {}
};

using ASTNodePtr = std::shared_ptr<ASTNode>;

class Expression : public ASTNode
{
};

class Number : public Expression
{
public:
    double value;
    Number(double v) : value(v) {}
    std::string toString() override
    {
        return "Number(" + std::to_string(value) + ")";
    }
    void accept(Interpreter &interp) override;
};

class Variable : public Expression
{
public:
    std::string name;
    Variable(const std::string &n) : name(n) {}
    std::string toString() override
    {
        return "Variable(" + name + ")";
    }
    void accept(Interpreter &interp) override;
};

class BinOp : public Expression
{
public:
    std::string op;
    std::shared_ptr<Expression> left, right;
    BinOp(std::shared_ptr<Expression> l, const std::string &oper, std::shared_ptr<Expression> r)
        : left(l), op(oper), right(r) {}
    std::string toString() override
    {
        return "BinOp(" + left->toString() + " " + op + " " + right->toString() + ")";
    }
    void accept(Interpreter &interp) override;
};

class FunctionCall : public Expression
{
public:
    std::string funcName;
    std::vector<std::shared_ptr<Expression>> args;
    FunctionCall(const std::string &name, const std::vector<std::shared_ptr<Expression>> &a)
        : funcName(name), args(a) {}
    std::string toString() override
    {
        std::ostringstream oss;
        oss << "FunctionCall(" << funcName << ", [";
        for (size_t i = 0; i < args.size(); i++)
        {
            oss << args[i]->toString();
            if (i < args.size() - 1)
                oss << ", ";
        }
        oss << "])";
        return oss.str();
    }
    void accept(Interpreter &interp) override;
};

class Statement : public ASTNode
{
};

class Assignment : public Statement
{
public:
    std::string varName;
    std::shared_ptr<Expression> expr;
    Assignment(const std::string &name, std::shared_ptr<Expression> e)
        : varName(name), expr(e) {}
    std::string toString() override
    {
        return "Assignment(" + varName + ", " + expr->toString() + ")";
    }
    void accept(Interpreter &interp) override;
};

class Print : public Statement
{
public:
    std::shared_ptr<Expression> expr;
    Print(std::shared_ptr<Expression> e) : expr(e) {}
    std::string toString() override
    {
        return "Print(" + expr->toString() + ")";
    }
    void accept(Interpreter &interp) override;
};

#endif // AST_H
