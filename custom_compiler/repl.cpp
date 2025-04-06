#include <iostream>
#include <string>
#include "ins_par.h"
#include "com_eng.h"
#include "utils.h"

void runREPL()
{
    std::string line;
    std::cout << "Custom Compiler REPL (type 'exit' to quit)\n";
    while (true)
    {
        std::cout << "> ";
        std::getline(std::cin, line);
        if (line == "exit")
            break;

        try
        {
            Instruction instr = parseInstruction(line);
            double result = ComputeEngine::compute(instr.opcode, instr.operand);
            printResult(result);
        }
        catch (const std::exception &e)
        {
            printError(e.what());
        }
    }
}
