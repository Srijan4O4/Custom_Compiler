#include <iostream>
#include <fstream>
#include <vector>
#include "tokeniser.h"
#include "parser.h"
#include "codegen.h"
#include "interpreter.h"
using namespace std;
int main()
{
    // Sample source code ----> expression is log(x) + 2*x.
    std::string src = R"(
int x = 10;
int z = log(x) + 2 * x;
print(z);
)";

    // STEP 1 : Tokenisation ---> Tokenise the source code to create a list of tokens.

    auto tokens = tokenize(src);
    cout << "<---Tokenisation--->" << std::endl;
    for (auto &token : tokens)
    {
        cout << "(" << token.first << ", " << token.second << ")" << " ";
    }
    cout << "\n";

    // STEP 2 : Parsing ---> Create a parser object and parse the tokens to create an AST.

    Parser parser(tokens);
    auto ast = parser.parse();
    cout << "\n<---Abstract Parse Tree--->" << "\n";
    for (auto &stmt : ast)
    {
        cout << stmt->toString() << "\n";
    }

    // STEP 3 : AST Traversal ---> Traverse the AST and print the nodes.

    CodeGen codegen;
    for (auto &stmt : ast)
    {
        codegen.generate(stmt);
    }
    cout << "\n<---ASM Output--->" << "\n";
    for (auto &instr : codegen.instructions)
    {
        cout << instr << "\n";
    }

    // STEP 4 : Code Generation ---> Generate assembly code from the AST.

    std::ofstream ofs("output.asm");
    for (auto &instr : codegen.instructions)
    {
        ofs << instr << std::endl;
    }
    ofs.close();

    // STEP 5 : Interpretation ---> Interpret the AST and execute the program.
    // This is a simple interpreter that evaluates the AST and prints the result.

    Interpreter interp;
    cout << "\n<---Result(s)--->" << endl;
    for (auto &stmt : ast)
    {
        stmt->accept(interp);
    }

    return 0;
}
