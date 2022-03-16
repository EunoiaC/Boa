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

    map<string, string> keyWords = {
            {"and",   AND},
            {"or",    OR},
            {"not",   NOT},
            {"contains",    CONTAINS},
            //{"get",    GET},
            {"return",    RETURN},
            {"continue",   CONTINUE},
            {"break",    BREAK},
            {"import",    IMPORT},
            {"from", FROM},
            {"if",    IF},
            {"else",  ELSE},
            {"do",    DO},
            {"elif",  ELIF},
            {"for",   FOR},
            {"iter",   ITER},
            {"to",    TO},
            {"chgby", CHGBY},
            {"while", WHILE},
            {"op",    OP},
            {"class",    CLASS},
            {"try",    TRY},
            {"catch",    CATCH},
            {"either", EITHER}
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
