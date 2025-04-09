## Details :
Name - Srijan Agrawal  
Semester  - 4th  
Roll No. - 23115095  
Branch - Computer Science & Engineering  
Subject - Compiler Design    
Proffesor - Mrs. Sonal Yadav    

---

## Custom Compiler Simulation in C++

This project implements a minimal compiler pipeline in C++ that demonstrates the key phases of compilation—tokenization, parsing, abstract syntax tree (AST) generation, code generation, and interpretation—while applying a simple optimization. Specifically, it recognizes the mathematical expression `log(x) + 2 * x` and replaces it with a custom instruction `LOGMULADD`.

---

## Project Structure

CustomCompilerCpp/
├── main.cpp  
├── tokeniser.h  
├── tokeniser.cpp  
├── ast.h  
├── parser.h  
├── parser.cpp  
├── codegen.h  
├── codegen.cpp  
├── interpreter.h  
├── interpreter.cpp  
└── README.md  

---

## A Simple Walkthrough using Example :
### Sample input 
```cpp
std::string src = R"(
int x = 10;
int z = log(x) + 2 * x;
print(z);
)";
```
### Code Output
```bash
<---Tokenisation--->
(INT, int)
(ID, x)
(ASSIGN, =)
(NUMBER, 10)
(SEMICOLON, ;)
(INT, int)
(ID, z)
(ASSIGN, =)
(ID, log)
(LPAREN, ()
(ID, x)
(RPAREN, ))
(ADD, +)
(NUMBER, 2)
(MUL, *)
(ID, x)
(SEMICOLON, ;)
(PRINT, print)
(LPAREN, ()
(ID, z)
(RPAREN, ))
(SEMICOLON, ;)
(EOF, )

<---Abstract Parse Tree--->
Assignment(x, Number(10))
Assignment(z, BinOp(FunctionCall(log, [Variable(x)]), +, BinOp(Number(2), * , Variable(x))))
Print(Variable(z))

<---ASM Output--->
MOV x, 10
LOGMULADD z, x
PRINT (z)

<---Result(s)--->
22.3026
```
--- 

### Why followed this technique making a mini compiler? Any other ways to do it?  
1. Modular Structure:  
-> Divided the project into components: tokenization, parsing, AST generation, code generation, and interpretation.  
-> Each module handles a specific aspect of compilation, making the overall process easier to understand and maintain.    

2. Handcrafted Components:  
-> Implemented a recursive-descent parser and custom pattern matching manually.  
-> Provides complete control over the process, which is especially valuable for educational purposes.  

3. Clarity and Instructiveness:  
-> The design demystifies how high-level code transforms into lower-level pseudo-assembly.  
-> Emphasizes modular design and clear separation of concerns, which are essential principles in compiler design.  

---

### Objective of the Mini Compiler :  
1. Educational Tool:  
-> Serves as a hands-on project to introduce the fundamental concepts of compiler design.  
-> Illustrates the complete compilation process, from code input to execution simulation.  

2. Pattern-Based Optimization:  
-> Demonstrates how specific patterns (e.g., log(x) + 2 * x) can be detected and replaced with a custom instruction (LOGMULADD).  
-> Highlights the potential for optimizing code by reducing multiple operations into a single instruction.  

3. Foundational Insights:  
-> Provides insights into core compiler components such as lexical analysis, AST construction, and code generation.  
-> Prepares learners for more complex topics in compiler construction and optimization techniques.

---
