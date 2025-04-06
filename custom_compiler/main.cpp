#include <fstream>
#include <iostream>
#include <string>

#include "ins_par.h"
#include "com_eng.h"
#include "utils.h"
#include <algorithm>
static inline std::string trim(const std::string &s)
{
    auto ws_front = std::find_if_not(s.begin(), s.end(), [](int c)
                                     { return std::isspace(c); });
    auto ws_back = std::find_if_not(s.rbegin(), s.rend(), [](int c)
                                    { return std::isspace(c); })
                       .base();
    return (ws_front < ws_back ? std::string(ws_front, ws_back) : std::string());
}

int main(int argc, char *argv[])
{
    const char *filename = (argc > 1 ? argv[1] : "ins.txt");
    std::ifstream in(filename);
    if (!in)
    {
        std::cerr << "Error: could not open '" << filename << "'\n";
        return 1;
    }

    std::string raw;
    while (std::getline(in, raw))
    {
        // trim whitespace
        std::string line = trim(raw);

        // skip empty or comment
        if (line.empty() || line[0] == '#')
            continue;

        // DEBUG
        std::cout << "[DEBUG] Processing line: '" << line << "'\n";

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
    return 0;
}