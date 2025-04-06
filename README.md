https://github.com/Srijan4O4/Custom_Compiler.git

This project is a minimal custom compiler and interpreter system designed to parse and execute a custom instruction:

It computes the value of  :
log(x) + 2 * x

Project Structure : 
.
├── com_eng.cpp          # ComputeEngine implementation
├── com_eng.h            # ComputeEngine header
├── compiler.exe         # (Possibly old binary, not needed)
├── custom_compiler.exe  # Compiled executable (final build)
├── ins.txt              # Input instruction file
├── ins_par.cpp          # Instruction parser implementation
├── ins_par.h            # Instruction parser header
├── main.cpp             # Main program to read & execute instructions
├── repl.cpp             # REPL mode (can be unused for file input mode)
├── run.txt              # (Optional) Sample output or run log
├── utils.cpp            # Utility functions
├── utils.h              # Utility header


Sample Instruction File 
# Each line represents an instruction
COMPUTE_LOG2X_PLUS_2X 5
COMPUTE_LOG2X_PLUS_2X 10
COMPUTE_LOG2X_PLUS_2X -1   # Should trigger domain error

How To Compile : 

g++ main.cpp ins_par.cpp com_eng.cpp utils.cpp -o custom_compiler.exe -std=c++17 -lm

How To Run : 

./custom_compiler.exe          # Uses 'ins.txt' by default
# or explicitly specify another input file
./custom_compiler.exe run.txt

Sample Output : 
Result: 11.6094
Result: 22.3026
Error: Log domain error: operand must be positive.


Thank You for Visiting my Custom Complier Project.
