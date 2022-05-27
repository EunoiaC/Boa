//
// Created by Aadi Yadav on 10/29/21.
//

#include <iostream>
#include "Lexer.h"

Lexer::Lexer(string fileText, string fileName, vector<string> lines) {
    currChar = '\0';
    error = nullptr;
    fTxt = fileText;
    this->fileName = fileName;
    this->lines = lines;
    charIdx = -1;
    charLineIdx = -1;
    lineIdx = 0;
    advance();
}

Lexer::~Lexer() {
    for (auto &p : charToToken) {
        delete p.second;
    }
}

void Lexer::advance() {
    currLine = lines[lineIdx];
    charIdx++;
    charLineIdx++;
    if (charIdx < fTxt.length()) {
        currChar = fTxt.at(charIdx);
        if (currChar == '\n') {
            if (lineIdx < lines.size() - 1) {
                lineIdx++;
                charLineIdx = 0;
            }
        }
    } else {
        currChar = '\0';
    }
    charToToken = {
            {';',  new BaseToken(TOK_TYPE::STOP_EXPR, charLineIdx, charLineIdx, lineIdx)},
            {',',  new BaseToken(TOK_TYPE::COMMA, charLineIdx, charLineIdx, lineIdx)},
            {'.',  new BaseToken(TOK_TYPE::DOT, charLineIdx, charLineIdx, lineIdx)},
            {'*',  new BaseToken(TOK_TYPE::MULTIPLY, charLineIdx, charLineIdx, lineIdx)},
            {'/',  new BaseToken(TOK_TYPE::DIVIDE, charLineIdx, charLineIdx, lineIdx)},
            {'^',  new BaseToken(TOK_TYPE::POWER, charLineIdx, charLineIdx, lineIdx)},
            {'%',  new BaseToken(TOK_TYPE::MOD, charLineIdx, charLineIdx, lineIdx)},
            {'?',  new BaseToken(TOK_TYPE::GET, charLineIdx, charLineIdx, lineIdx)},
            {'(',  new BaseToken(TOK_TYPE::L_PAREN, charLineIdx, charLineIdx, lineIdx)},
            {')',  new BaseToken(TOK_TYPE::R_PAREN, charLineIdx, charLineIdx, lineIdx)},
            {'[',  new BaseToken(TOK_TYPE::L_BRACKET, charLineIdx, charLineIdx, lineIdx)},
            {']',  new BaseToken(TOK_TYPE::R_BRACKET, charLineIdx, charLineIdx, lineIdx)},
            {'{',  new BaseToken(TOK_TYPE::L_CURLY_BRACKET, charLineIdx, charLineIdx, lineIdx)},
            {'}',  new BaseToken(TOK_TYPE::R_CURLY_BRACKET, charLineIdx, charLineIdx, lineIdx)},
            {':',  new BaseToken(TOK_TYPE::COLON, charLineIdx, charLineIdx, lineIdx)},
            {'\n', new BaseToken(TOK_TYPE::STOP_EXPR, charLineIdx, charLineIdx,
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
    TOK_TYPE type = TOK_TYPE::IDENTIFIER;
    if (keyWords.find(identifier) != keyWords.end()) {
        type = keyWords.at(identifier);
    }
    Token<string> *token = new Token<string>(type, identifier, start, charLineIdx - 1, currLineIdx);
    token->fTxt = currLine;
    token->line = lineIdx;
    return token;
}

Token<string> *Lexer::makeString() {
    char stopChar = currChar; //the char that ends the string (" or ')
    string oppositeStopChar = "\0";
    if (stopChar == '\'') {
        oppositeStopChar = "\"";
    } else {
        oppositeStopChar = "\'";
    }
    string str;
    int start = charLineIdx;
    int currLineIdx = lineIdx;
    advance();
    while (currChar != stopChar) {
        char toAdd = currChar;
        if (toAdd == '\\') {
            advance();
            // \n
            if (currChar == 'n') {
                toAdd = '\n';
            }
            // \t
            else if (currChar == 't') {
                toAdd = '\t';
            }
            // \r
            else if (currChar == 'r') {
                toAdd = '\r';
            }
            // \b
            else if (currChar == 'b') {
                toAdd = '\b';
            }
            // \f
            else if (currChar == 'f') {
                toAdd = '\f';
            }
        }
        if (currChar == '\n') {
            error = new Error(
                    start,
                    start,
                    currLineIdx,
                    fileName,
                    lines[currLineIdx],
                    "SyntaxError",
                    "Could not find closing " + oppositeStopChar + string(1, stopChar) + oppositeStopChar +
                    " for this " + oppositeStopChar + string(1, stopChar) + oppositeStopChar
            );
            return nullptr;
        }
        str += toAdd;
        advance();
    }
    advance(); //advance past the stop char
    return new Token<string>(TOK_TYPE::T_STRING, str, start, charLineIdx - 1, currLineIdx);
}

Token<double> *Lexer::makeNumber() {
    string number;
    int start = charLineIdx;
    int currLineIdx = lineIdx;
    while ((NUMBERS + ".").find(currChar) != string::npos) {
        number += currChar;
        advance();
    }
    return new Token<double>(TOK_TYPE::T_NUM, stod(number), start, charLineIdx - 1, currLineIdx);
}

Token<string> *Lexer::minusOperation() {
    int start = charLineIdx;
    int currLineIdx = lineIdx;
    advance();
    if (currChar == '=') {
        advance();
        return new Token<string>(TOK_TYPE::MINUS_EQUAL, "-=", start, charLineIdx - 1, currLineIdx);
    } else if (currChar == '-') {
        advance();
        return new Token<string>(TOK_TYPE::MINUS_MINUS, "--", start, charLineIdx - 1, currLineIdx);
    }
    return new Token<string>(TOK_TYPE::MINUS, "-", start, start, currLineIdx);
}

Token<string> *Lexer::makeNotEquals() {
    int start = charLineIdx;
    int currLineIdx = lineIdx;
    advance();
    if (currChar == '=') {
        advance();
        return new Token<string>(TOK_TYPE::NOT_EQUAL, "!=", start, charLineIdx - 1, currLineIdx);
    }
    return new Token<string>(TOK_TYPE::NOT, "!", start, charLineIdx - 1, currLineIdx);

}

Token<string> *Lexer::makeEquals() {
    int start = charLineIdx;
    int currLineIdx = lineIdx;
    TOK_TYPE type = TOK_TYPE::EQUAL;
    advance();
    if (currChar == '=') {
        advance();
        type = TOK_TYPE::EQUAL_EQUAL;
    }
    return new Token<string>(type, to_string(type), start, charLineIdx - 1, currLineIdx);
}

Token<string> *Lexer::makeLessThan() {
    int start = charLineIdx;
    int currLineIdx = lineIdx;
    TOK_TYPE type = TOK_TYPE::LESS_THAN;
    advance();
    if (currChar == '=') {
        advance();
        type = TOK_TYPE::LESS_THAN_EQUAL;
    }
    return new Token<string>(type, to_string(type), start, charLineIdx - 1, currLineIdx);
}

Token<string> *Lexer::makeGreaterThan() {
    int start = charLineIdx;
    int currLineIdx = lineIdx;
    TOK_TYPE type = TOK_TYPE::GREATER_THAN;
    advance();
    if (currChar == '=') {
        advance();
        type = TOK_TYPE::GREATER_THAN_EQUAL;
    }
    return new Token<string>(type, to_string(type), start, charLineIdx - 1, currLineIdx);
}

Token<string> *Lexer::plusOperation() {
    int start = charLineIdx;
    int currLineIdx = lineIdx;
    advance();
    if (currChar == '=') {
        advance();
        return new Token<string>(TOK_TYPE::PLUS_EQUAL, "+=", start, charLineIdx - 1, currLineIdx);
    } else if (currChar == '+') {
        advance();
        return new Token<string>(TOK_TYPE::PLUS_PLUS, "++", start, charLineIdx - 1, currLineIdx);
    }
    return new Token<string>(TOK_TYPE::PLUS, "+", start, start, currLineIdx);
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
        } else if (currChar == '#') {
            while (currChar != '\n') {
                advance();
            }
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
            Token<string> *tok = makeString();
            if (tok == nullptr) {
                return {};
            }
            toks.push_back(tok);
        } else if ((LETTERS + "_").find(currChar) != string::npos) {
            toks.push_back(makeIdentifier());
        } else if (NUMBERS.find(currChar) != string::npos) {
            toks.push_back(makeNumber());
        } else {
            if (isspace(currChar)) {
                advance();
            } else {
                error = new Error(
                        charLineIdx,
                        charLineIdx,
                        lineIdx,
                        fileName,
                        lines[lineIdx],
                        "UnknownCharacterError",
                        "Character can't be used"
                );
                return {};
            }

        }
    }
    toks.push_back(new BaseToken(TOK_TYPE::END_OF_FILE, charLineIdx, charLineIdx, lineIdx - 1)); //-1 since the last line is empty
    return toks;
}