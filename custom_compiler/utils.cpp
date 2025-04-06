#include "utils.h"
#include <iostream>

void printResult(double result)
{
    std::cout << "Result: " << result << std::endl;
}

void printError(const std::string &errorMsg)
{
    std::cerr << "Error: " << errorMsg << std::endl;
}
