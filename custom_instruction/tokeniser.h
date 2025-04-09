#ifndef TOKENISER_H
#define TOKENISER_H

#include <string>
#include <vector>
#include <utility>
using namespace std;

using Token = pair<string,string>;

vector<Token> tokenize(const string &code);

#endif // TOKENISER_H
