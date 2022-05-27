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
        IF,
        DO,
        ELSE,
        FOR,
        ITER,
        WHILE,
        CHGBY,
        TO,
        OP,
        CLASS,
        INFIX,
        USES,
        TRY,
        CATCH,
        RETURN,
        BREAK,
        AWAIT,
        IMPORT,
        FROM,
        CONTINUE,
        ELIF,
        IDENTIFIER,
        GET,
        CONTAINS,
        PLUS,
        MINUS,
        MULTIPLY,
        DIVIDE,
        POWER,
        MOD,
        EQUAL,
        AND,
        OR,
        EITHER,
        NOT,
        PLUS_EQUAL,
        PLUS_PLUS,
        MINUS_EQUAL,
        MINUS_MINUS,
        LESS_THAN,
        GREATER_THAN,
        GREATER_THAN_EQUAL,
        LESS_THAN_EQUAL,
        EQUAL_EQUAL,
        NOT_EQUAL,
        L_PAREN,
        R_PAREN,
        L_BRACKET,
        R_BRACKET,
        L_CURLY_BRACKET,
        R_CURLY_BRACKET,
        COLON,
        COMMA,
        DOT,
        END_OF_FILE,
        STOP_EXPR,
        //Value Types:
        T_STRING,
        T_FUTURE,
        T_FUNC,
        T_NUM,
        T_CLASS,
        T_LIST,
        T_MAP,
        T_FILE
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
