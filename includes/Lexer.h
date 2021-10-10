//
// Created by Preeti Thorat on 10/6/21.
//

#ifndef BOA_LEXER_H
#define BOA_LEXER_H

#include <string>
#include <list>
#include "Token.h"

using namespace std;

class Lexer {
    string text;
public:
    Lexer(string fTxt);
    list<Token> tokens();
};

#endif