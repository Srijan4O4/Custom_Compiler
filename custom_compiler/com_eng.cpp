#include "com_eng.h"
#include <cmath>
#include <stdexcept>

double ComputeEngine::compute(const std::string &opcode, double operand)
{
    if (opcode == "COMPUTE_LOG2X_PLUS_2X")
    {
        if (operand <= 0)
        {
            throw std::domain_error("Log domain error: operand must be positive.");
        }
        return std::log2(operand) + 2 * operand;
    }
    throw std::invalid_argument("Unknown opcode: " + opcode);
}
