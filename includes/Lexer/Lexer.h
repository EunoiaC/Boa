//
// Created by Aadi Yadav on 10/29/21.
//
#pragma once
#ifndef BOA_LEXER_H
#define BOA_LEXER_H

#include <vector>
#include <map>
#include <fstream>
#include "../Token/Token.h"
#include "../Token/TokenType.h"

using namespace std;

class Lexer {
private:
    string currLine;
    /**
     * The index of the character relative to the line
     */
    int charLineIdx;
    /**
     * The current line the lexer is on
     */
    int lineIdx;
    /**
     * Current character index
     */
    int charIdx;
    /**
     * Current character
     */
    char currChar;
    string fileName;
    ifstream file;
public:
    Lexer(string fileText, string fileName);
    vector<string> keyWords = {
            "var"
    };
    /**
     * Map assigning each possible character a token type
     */
    map<char, BaseToken *> charToToken;
    /**
     * The file text used to make the tokens
     */
    string fTxt;

    /**
     * @return A list of tokens made after scanning the file text
     */
    vector<BaseToken *> makeTokens();

    /**
     * Advances the token index and updates currChar to the next char
     */
    void advance();

    /**
     * @return Makes a set of characters into an identifier
     */
    Token<string> *makeIdentifier();

    Token<string> *plusOperation();
    Token<string> *minusOperation();

    /**
     * @return Makes a set of characters into a Number
     */
    Token<double> *makeNumber();

    /**
     * @return Makes a set of characters into a String
     */
    Token<string> *makeString();
};


#endif //BOA_LEXER_H
