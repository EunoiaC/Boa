//
// Created by Aadi Yadav on 10/29/21.
//

#include <iostream>
#include "Lexer.h"

Lexer::Lexer(string fileText, string fileName) {
    currChar = '\0';
    error = nullptr;
    fTxt = fileText;
    this->fileName = fileName;
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
            {';',  new BaseToken(STOP_EXPR, charLineIdx, charLineIdx, lineIdx)},
            {',',  new BaseToken(COMMA, charLineIdx, charLineIdx, lineIdx)},
            {'*',  new BaseToken(MULTIPLY, charLineIdx, charLineIdx, lineIdx)},
            {'/',  new BaseToken(DIVIDE, charLineIdx, charLineIdx, lineIdx)},
            {'^',  new BaseToken(POWER, charLineIdx, charLineIdx, lineIdx)},
            {'%',  new BaseToken(MOD, charLineIdx, charLineIdx, lineIdx)},
            {'?',  new BaseToken(GET, charLineIdx, charLineIdx, lineIdx)},
            {'(',  new BaseToken(L_PAREN, charLineIdx, charLineIdx, lineIdx)},
            {')',  new BaseToken(R_PAREN, charLineIdx, charLineIdx, lineIdx)},
            {'[',  new BaseToken(L_BRACKET, charLineIdx, charLineIdx, lineIdx)},
            {']',  new BaseToken(R_BRACKET, charLineIdx, charLineIdx, lineIdx)},
            {'{',  new BaseToken(L_CURLY_BRACKET, charLineIdx, charLineIdx, lineIdx)},
            {'}',  new BaseToken(R_CURLY_BRACKET, charLineIdx, charLineIdx, lineIdx)},
            {':',  new BaseToken(COLON, charLineIdx, charLineIdx, lineIdx)},
            {'\n', new BaseToken(STOP_EXPR, charLineIdx, charLineIdx,
                                 lineIdx - 1)}//-1 because the lineIdx is incremented after the newline
    };
}

Token<string> *Lexer::makeIdentifier() {
    string identifier;
    int start = charLineIdx;
    int currLineIdx = lineIdx;
    while ((LETTERS + "_" + NUMBERS).find(currChar) != string::npos) {
        identifier += currChar;
        advance();
    }
    string type = IDENTIFIER;
    if (keyWords.find(identifier) != keyWords.end()) {
        type = keyWords.at(identifier);
    }
    return new Token<string>(type, identifier, start, charLineIdx - 1, currLineIdx);
}

Token<string> *Lexer::makeString() {
    char stopChar = currChar; //the char that ends the string (" or ')
    string str;
    int start = charLineIdx;
    int currLineIdx = lineIdx;
    advance();
    while (currChar != stopChar) {
        str += currChar;
        advance();
    }
    advance(); //advance past the stop char
    return new Token<string>(T_STRING, str, start, charLineIdx - 1, currLineIdx);
}

Token<double> *Lexer::makeNumber() {
    string number;
    int start = charLineIdx;
    int currLineIdx = lineIdx;
    while ((NUMBERS + ".").find(currChar) != string::npos) {
        number += currChar;
        advance();
    }
    return new Token<double>(T_NUM, stod(number), start, charLineIdx - 1, currLineIdx);
}

Token<string> *Lexer::minusOperation() {
    int start = charLineIdx;
    int currLineIdx = lineIdx;
    advance();
    if (currChar == '=') {
        advance();
        return new Token<string>(MINUS_EQUAL, "-=", start, charLineIdx - 1, currLineIdx);
    } else if (currChar == '-') {
        advance();
        return new Token<string>(MINUS_MINUS, "--", start, charLineIdx - 1, currLineIdx);
    } else if (currChar == '>') {
        advance();
        return new Token<string>(ARROW, "->", start, charLineIdx - 1, currLineIdx);
    }
    return new Token<string>(MINUS, "-", start, start, currLineIdx);
}

Token<string> *Lexer::makeNotEquals() {
    int start = charLineIdx;
    int currLineIdx = lineIdx;
    advance();
    if (currChar == '=') {
        advance();
        return new Token<string>(NOT_EQUAL, "!=", start, charLineIdx - 1, currLineIdx);
    }
    return new Token<string>(NOT, "!", start, charLineIdx - 1, currLineIdx);

}

Token<string> *Lexer::makeEquals() {
    int start = charLineIdx;
    int currLineIdx = lineIdx;
    string type = EQUAL;
    advance();
    if (currChar == '=') {
        advance();
        type = EQUAL_EQUAL;
    }
    return new Token<string>(type, type, start, charLineIdx - 1, currLineIdx);
}

Token<string> *Lexer::makeLessThan() {
    int start = charLineIdx;
    int currLineIdx = lineIdx;
    string type = LESS_THAN;
    advance();
    if (currChar == '=') {
        advance();
        type = LESS_THAN_EQUAL;
    }
    return new Token<string>(type, type, start, charLineIdx - 1, currLineIdx);
}

Token<string> *Lexer::makeGreaterThan() {
    int start = charLineIdx;
    int currLineIdx = lineIdx;
    string type = GREATER_THAN;
    advance();
    if (currChar == '=') {
        advance();
        type = GREATER_THAN_EQUAL;
    }
    return new Token<string>(type, type, start, charLineIdx - 1, currLineIdx);
}

Token<string> *Lexer::plusOperation() {
    int start = charLineIdx;
    int currLineIdx = lineIdx;
    advance();
    if (currChar == '=') {
        advance();
        return new Token<string>(PLUS_EQUAL, "+=", start, charLineIdx - 1, currLineIdx);
    } else if (currChar == '+') {
        advance();
        return new Token<string>(PLUS_PLUS, "++", start, charLineIdx - 1, currLineIdx);
    }
    return new Token<string>(PLUS, "+", start, start, currLineIdx);
}

vector<BaseToken *> Lexer::makeTokens() {
    vector<BaseToken *> toks;
    while (currChar != '\0') {
        if (charToToken.count(currChar) != 0) {
            if (currChar == '\n') {
                charLineIdx = -1; //reset the charLineIdx
            }
            toks.push_back(charToToken.find(currChar)->second);
            advance();
        } else if (currChar == '!') {
            toks.push_back(makeNotEquals());
        } else if (currChar == '<') {
            toks.push_back(makeLessThan());
        } else if (currChar == '>') {
            toks.push_back(makeGreaterThan());
        } else if (currChar == '=') {
            toks.push_back(makeEquals());
        } else if (currChar == '+') {
            toks.push_back(plusOperation());
        } else if (currChar == '-') {
            toks.push_back(minusOperation());
        } else if (currChar == '"' || currChar == '\'') {
            toks.push_back(makeString());
        } else if ((LETTERS + "_").find(currChar) != string::npos) {
            toks.push_back(makeIdentifier());
        } else if (NUMBERS.find(currChar) != string::npos) {
            toks.push_back(makeNumber());
        } else {
            if(isspace(currChar)) {
                advance();
            } else {
                error = new Error(
                        charLineIdx,
                        charLineIdx,
                        lineIdx,
                        fileName,
                        fTxt,
                        "UnknownCharacterError",
                        "Character can't be used"
                );
                return {};
            }

        }
    }
    toks.push_back(new BaseToken(END_OF_FILE, charIdx, charIdx, lineIdx));
    return toks;
}