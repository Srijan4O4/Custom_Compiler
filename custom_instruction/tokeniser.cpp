#include "tokeniser.h"
#include <regex>
#include <stdexcept>
#include <iterator>
std::vector<Token> tokenize(const std::string &code)
{
    std::vector<Token> tokens;
    // Define a regex pattern for tokens.
    std::regex tokenPatterns(
        "(int)|"                    //1. INT
        "(print)|"                  //2. PRINT 
        "([0-9]+)|"                 //3. NUMBER
        "([a-zA-Z_][a-zA-Z0-9_]*)|" //4. Identifier
        "(=)|"                      //5. ASSIGN
        "(\\*)|"                    //6. MUL
        "(\\+)|"                    //7. ADD
        "(\\()|"                    //8. LPAREN
        "(\\))|"                    //9. RPAREN
        "(;)|"                      //10. SEMICOLON
        "([ \\t]+)|"                //11. Whitespace
        "(\n)"                      //12. Newline
    );
    auto words_begin = std::sregex_iterator(code.begin(), code.end(), tokenPatterns);
    auto words_end = std::sregex_iterator();

    for (std::sregex_iterator it = words_begin; it != words_end; ++it)
    {
        std::smatch match = *it;
        if (match[1].matched)
        {
            tokens.push_back({"INT", match[1].str()});
        }
        else if (match[2].matched)
        {
            tokens.push_back({"PRINT", match[2].str()});
        }
        else if (match[3].matched)
        {
            tokens.push_back({"NUMBER", match[3].str()});
        }
        else if (match[4].matched)
        {
            tokens.push_back({"ID", match[4].str()});
        }
        else if (match[5].matched)
        {
            tokens.push_back({"ASSIGN", match[5].str()});
        }
        else if (match[6].matched)
        {
            tokens.push_back({"MUL", match[6].str()});
        }
        else if (match[7].matched)
        {
            tokens.push_back({"ADD", match[7].str()});
        }
        else if (match[8].matched)
        {
            tokens.push_back({"LPAREN", match[8].str()});
        }
        else if (match[9].matched)
        {
            tokens.push_back({"RPAREN", match[9].str()});
        }
        else if (match[10].matched)
        {
            tokens.push_back({"SEMICOLON", match[10].str()});
        }
        else if (match[11].matched)
        {
        }
        else if (match[12].matched)
        {
        }
    }
    
    tokens.push_back({"EOF", ""});
    return tokens;
}
