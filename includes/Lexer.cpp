//
// Created by Preeti Thorat on 10/29/21.
//

#include "Lexer.h"

Lexer::Lexer(string fileText) {
    currChar = '\0';
    fTxt = fileText;
    charIdx = -1;
    charLineIdx = -1;
    lineIdx = 0; //0 is first line
    advance();
}

void Lexer::advance() {
    charIdx++;
    charLineIdx++;
    if (charIdx < fTxt.length()) {
        currChar = fTxt.at(charIdx);
        if (currChar == '\n') {
            lineIdx++;
        }
    } else {
        currChar = '\0';
    }
    charToToken = {
            {'+',  new BaseToken(PLUS, charLineIdx, charLineIdx, lineIdx)},
            {'-',  new BaseToken(MINUS, charLineIdx, charLineIdx, lineIdx)},
            {'*',  new BaseToken(MULTIPLY, charLineIdx, charLineIdx, lineIdx)},
            {'/',  new BaseToken(DIVIDE, charLineIdx, charLineIdx, lineIdx)},
            {'=',  new BaseToken(EQUAL, charLineIdx, charLineIdx, lineIdx)},
            {'<',  new BaseToken(LESS_THAN, charLineIdx, charLineIdx, lineIdx)},
            {'>',  new BaseToken(GREATER_THAN, charLineIdx, charLineIdx, lineIdx)},
            {'(',  new BaseToken(L_PAREN, charLineIdx, charLineIdx, lineIdx)},
            {')',  new BaseToken(R_PAREN, charLineIdx, charLineIdx, lineIdx)},
            {'{',  new BaseToken(L_BRACKET, charLineIdx, charLineIdx, lineIdx)},
            {'}',  new BaseToken(R_BRACKET, charLineIdx, charLineIdx, lineIdx)},
            {'\n', new BaseToken(STOP_EXPR, charLineIdx, charLineIdx,
                                 lineIdx - 1)}//-1 because the lineIdx is incremented after the newline
    };
}

Token<string> *Lexer::makeIdentifier() {
    string identifier = "";
    int start = charLineIdx;
    while ((LETTERS + "_").find(currChar) != string::npos) {
        identifier += currChar;
        advance();
    }
    return new Token<string>(T_IDENTIFIER, identifier, start, charLineIdx - 1, lineIdx);
}

Token<string> *Lexer::makeString() {
    char stopChar = currChar; //the char that ends the string (" or ')
    string str = "";
    int start = charLineIdx;
    advance();
    while(currChar != stopChar) {
        str += currChar;
        advance();
    }
    advance(); //advance past the stop char
    return new Token<string>(T_STRING, str, start, charLineIdx - 1, lineIdx);
}

Token<double> *Lexer::makeNumber() {
    string number = "";
    int start = charLineIdx;
    while ((NUMBERS + ".").find(currChar) != string::npos) {
        number += currChar;
        advance();
    }
    return new Token<double>(T_NUM, stod(number), start, charLineIdx - 1, lineIdx);
}

vector<BaseToken *> Lexer::makeTokens() {
    vector<BaseToken *> toks;
    while (currChar != '\0') {
        if (charToToken.count(currChar) != 0) {
            if(currChar == '\n') {
                charLineIdx = -1; //reset the charLineIdx
            }
            toks.push_back(charToToken.find(currChar)->second);
            advance();
        } else if (currChar == '"' || currChar == '\'') {
            toks.push_back(makeString());
        } else if ((LETTERS + "_").find(currChar) != string::npos) {
            toks.push_back(makeIdentifier());
        } else if (NUMBERS.find(currChar) != string::npos) {
            toks.push_back(makeNumber());
        } else {
            advance();
        }
    }
    toks.push_back(new BaseToken(END_OF_FILE, charIdx, charIdx, lineIdx));
    return toks;
}