//
// Created by Preeti Thorat on 12/6/21.
//

#ifndef BOA_BASETOKEN_H
#define BOA_BASETOKEN_H

#include <string>

using namespace std;

class BaseToken {
public:
    string fName, fTxt;

    enum TOK_TYPE {
        IF = 0,
        DO = 1,
        ELSE = 2,
        FOR = 3,
        ITER = 4,
        WHILE = 5,
        CHGBY = 6,
        TO = 7,
        OP = 8,
        CLASS = 9,
        INFIX = 10,
        USES = 11,
        TRY = 12,
        CATCH = 13,
        RETURN = 14,
        BREAK = 15,
        AWAIT = 16,
        IMPORT = 17,
        FROM = 18,
        CONTINUE = 19,
        ELIF = 20,
        IDENTIFIER = 21,
        GET = 22,
        CONTAINS = 23,
        PLUS = 24,
        MINUS = 25,
        MULTIPLY = 26,
        DIVIDE = 27,
        POWER = 28,
        MOD = 29,
        EQUAL = 30,
        AND = 31,
        OR = 32,
        EITHER = 33,
        NOT = 34,
        PLUS_EQUAL = 35,
        PLUS_PLUS = 36,
        MINUS_EQUAL = 37,
        MINUS_MINUS = 38,
        LESS_THAN = 39,
        GREATER_THAN = 40,
        GREATER_THAN_EQUAL = 41,
        LESS_THAN_EQUAL = 42,
        EQUAL_EQUAL = 43,
        NOT_EQUAL = 44,
        L_PAREN = 45,
        R_PAREN = 46,
        L_BRACKET = 47,
        R_BRACKET = 48,
        L_CURLY_BRACKET = 49,
        R_CURLY_BRACKET = 50,
        COLON = 51,
        COMMA = 52,
        DOT = 53,
        END_OF_FILE = 54,
        STOP_EXPR = 55,
        //Value Types:
        T_STRING = 56,
        T_FUTURE = 57,
        T_FUNC = 58,
        T_NUM = 59,
        T_CLASS = 60,
        T_LIST = 61,
        T_MAP = 62,
        T_FILE = 63
    };

    BaseToken(TOK_TYPE t, int start_pos, int end_pos, int line_num);

    ~BaseToken();

    /**
     * The starting position of the token at a certain line
     */
    int posStart;
    /**
     * The ending position of the token at a certain line
     */
    int posEnd;
    /**
     * The line the token is on
     */
    int line;
    /**
     * The type of the token, can be a supported object type, identifier, keyword, or a symbol
     */
    TOK_TYPE type;

    /**
     * @return The type of token
     */
    TOK_TYPE getType();

    /**
     * @return Type of the Token
     */
    virtual string toString();

    /**
     * @return Position data of the Token
     */
    string posData();
};


#endif //BOA_BASETOKEN_H
