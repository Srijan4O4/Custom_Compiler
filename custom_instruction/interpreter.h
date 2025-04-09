#ifndef INTERPRETER_H
#define INTERPRETER_H

#include "ast.h"
#include <unordered_map>
#include <string>

class Interpreter
{
public:
    std::unordered_map<std::string, double> env;
    void visit(Number *num);
    void visit(Variable *var);
    void visit(BinOp *bin);
    void visit(FunctionCall *func);
    void visit(Assignment *assign);
    void visit(Print *print);
};

#endif // INTERPRETER_H
