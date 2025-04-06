#ifndef COMPUTE_ENGINE_H
#define COMPUTE_ENGINE_H

#include <string>

class ComputeEngine
{
public:
    static double compute(const std::string &opcode, double operand);
};

#endif // COMPUTE_ENGINE_H
    