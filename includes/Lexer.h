//
// Created by Administrator on 10/13/2021.
//

#ifndef BOA_LEXER_H
#define BOA_LEXER_H

#include <string>
#include "Token.cpp"
#include <list>

using namespace std;

class Lexer {
private:
    /**
     * Text used to create tokens
     */
    string text;
    /**
     * Index of the character the lexer is at
     */
    int idx = -1;
    /**
     * The current character the lexer is on
     */
    char currentChar = '\0';
public:
    Lexer(string txt);
    /**
     * Function that makes tokens by going through text.
     * @return list of tokens
     */
    list<Token> makeTokens();
    /**
     * Advances to the next character in the text
     */
    void advance();
};


#endif //BOA_LEXER_H
