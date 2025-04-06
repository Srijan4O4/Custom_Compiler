#include "ins_par.h"
#include <sstream>

Instruction::Instruction(const std::string &op, double val) : opcode(op), operand(val) {}

Instruction parseInstruction(const std::string &line)
{
    std::istringstream iss(line);
    std::string opcode;
    double operand;
    iss >> opcode >> operand;
    return Instruction(opcode, operand);
}
