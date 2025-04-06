#ifndef INSTRUCTION_PARSER_H
#define INSTRUCTION_PARSER_H

#include <string>

class Instruction
{
public:
    std::string opcode;
    double operand;

    Instruction(const std::string &op, double val);
};

Instruction parseInstruction(const std::string &line);

#endif // INSTRUCTION_PARSER_H
