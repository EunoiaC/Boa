//
// Created by Preeti Thorat on 10/29/21.
//

#include "Lexer.h"

Lexer::Lexer(string fileText) {
    currChar = '\0';
    fTxt = fileText;
    charIdx = -1;
    lineIdx = 0; //0 is first line
    advance();
}

void Lexer::advance() {
    charIdx++;
    if (charIdx < fTxt.length()) {
        currChar = fTxt.at(charIdx);
        if (currChar == '\n') {
            lineIdx++;
        }
    } else {
        currChar = '\0';
    }
    charToToken = {
            {'+',  new BaseToken(PLUS, charIdx, charIdx, lineIdx)},
            {'-',  new BaseToken(MINUS, charIdx, charIdx, lineIdx)},
            {'*',  new BaseToken(MULTIPLY, charIdx, charIdx, lineIdx)},
            {'/',  new BaseToken(DIVIDE, charIdx, charIdx, lineIdx)},
            {'=',  new BaseToken(EQUAL, charIdx, charIdx, lineIdx)},
            {'<',  new BaseToken(LESS_THAN, charIdx, charIdx, lineIdx)},
            {'>',  new BaseToken(GREATER_THAN, charIdx, charIdx, lineIdx)},
            {'(',  new BaseToken(L_PAREN, charIdx, charIdx, lineIdx)},
            {')',  new BaseToken(R_PAREN, charIdx, charIdx, lineIdx)},
            {'{',  new BaseToken(L_BRACKET, charIdx, charIdx, lineIdx)},
            {'}',  new BaseToken(R_BRACKET, charIdx, charIdx, lineIdx)},
            {'\n', new BaseToken(STOP_EXPR, charIdx, charIdx,
                                 lineIdx - 1)}//-1 because the lineIdx is incremented after the newline
    };
}

Token<string> *Lexer::makeIdentifier() {
    string identifier = "";
    int start = charIdx;
    while ((LETTERS + "_").find(currChar) != string::npos) {
        identifier += currChar;
        advance();
    }
    return new Token<string>(T_IDENTIFIER, identifier, start, charIdx - 1, lineIdx);
}

Token<string> *Lexer::makeString() {
    char stopChar = currChar; //the char that ends the string (" or ')
    string str = "";
    int start = charIdx;
    advance();
    while(currChar != stopChar) {
        str += currChar;
        advance();
    }
    advance(); //advance past the stop char
    return new Token<string>(T_STRING, str, start, charIdx - 1, lineIdx);
}

Token<double> *Lexer::makeNumber() {
    string number = "";
    int start = charIdx;
    while ((NUMBERS + ".").find(currChar) != string::npos) {
        number += currChar;
        advance();
    }
    return new Token<double>(T_NUM, stod(number), start, charIdx - 1, lineIdx);
}

vector<BaseToken *> Lexer::makeTokens() {
    vector<BaseToken *> toks;
    while (currChar != '\0') {
        if (charToToken.count(currChar) != 0) {
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