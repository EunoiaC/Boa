//
// Created by Aadi Yadav on 10/29/21.
//

#ifndef BOA_LEXER_H
#define BOA_LEXER_H

#include <vector>
#include <map>
#include <fstream>
#include "../Token/Token.h"

using namespace std;
using TOK_TYPE = BaseToken::TOK_TYPE;

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
    vector<string> lines;
public:
    Error * error;
    Lexer(string fileText, string fileName, vector<string> lines);
    ~Lexer();

    map<string, TOK_TYPE> keyWords = {
            {"and",   TOK_TYPE::AND},
            {"or",    TOK_TYPE::OR},
            {"not",   TOK_TYPE::NOT},
            {"contains",    TOK_TYPE::CONTAINS},
            //{"get",    GET},
            {"return",    TOK_TYPE::RETURN},
            {"continue",   TOK_TYPE::CONTINUE},
            {"break",    TOK_TYPE::BREAK},
            {"import",    TOK_TYPE::IMPORT},
            {"from", TOK_TYPE::FROM},
            {"if",    TOK_TYPE::IF},
            {"else",  TOK_TYPE::ELSE},
            {"do",    TOK_TYPE::DO},
            {"elif",  TOK_TYPE::ELIF},
            {"for",   TOK_TYPE::FOR},
            {"iter",   TOK_TYPE::ITER},
            {"to",    TOK_TYPE::TO},
            {"chgby", TOK_TYPE::CHGBY},
            {"while", TOK_TYPE::WHILE},
            {"op",    TOK_TYPE::OP},
            {"class",    TOK_TYPE::CLASS},
            {"try",    TOK_TYPE::TRY},
            {"catch",    TOK_TYPE::CATCH},
            {"either", TOK_TYPE::EITHER},
            {"await", TOK_TYPE::AWAIT},
            {"infix", TOK_TYPE::INFIX},
            {"uses", TOK_TYPE::USES}
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

    Token<string> *makeEquals();

    Token<string> *makeNotEquals();

    Token<string> *makeGreaterThan();

    Token<string> *makeLessThan();

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
