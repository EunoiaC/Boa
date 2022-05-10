//
// Created by Aadi Yadav on 10/13/21.
//

#ifndef BOA_TOKEN_H
#define BOA_TOKEN_H

#include "../Values/BaseValues/Value.h"
#include "../Values/String/String.h"
#include "../Values/Number/Number.h"
#include "BaseToken.h"

using namespace std;

//All token types
static const string IF = "IF";
static const string DO = "DO";
static const string ELSE = "ELSE";
static const string FOR = "FOR";
static const string ITER = "ITER";
static const string WHILE = "WHILE";
static const string CHGBY = "CHANGE_BY";
static const string TO = "TO";
static const string OP = "OP";
static const string CLASS = "CLASS";

static const string INFIX = "INFIX";
static const string USES = "USES";

static const string TRY = "TRY";
static const string CATCH = "CATCH";

static const string RETURN = "RETURN";
static const string BREAK = "BREAK";
static const string AWAIT = "AWAIT";
static const string IMPORT = "IMPORT";
static const string FROM = "FROM";
static const string CONTINUE = "CONTINUE";

static const string ELIF = "ELIF";
static const string IDENTIFIER = "IDENTIFIER";
static const string GET = "GET";
static const string CONTAINS = "CONTAINS";
static const string PLUS = "PLUS";
static const string MINUS = "MINUS";
static const string MULTIPLY = "MULTIPLY";
static const string DIVIDE = "DIVIDE";
static const string POWER = "POWER";
static const string MOD = "MOD";
static const string EQUAL = "EQUAL";
static const string AND = "AND";
static const string OR = "OR";
static const string EITHER = "EITHER";
static const string NOT = "NOT";
static const string PLUS_EQUAL = "PLUS_EQUAL";
static const string PLUS_PLUS = "PLUS_PLUS";
static const string MINUS_MINUS = "MINUS_MINUS";
static const string MINUS_EQUAL = "MINUS_EQUAL";
static const string LESS_THAN = "LESS_THAN";
static const string GREATER_THAN = "GREATER_THAN";
static const string GREATER_THAN_EQUAL = "GREATER_THAN_EQUAL";
static const string LESS_THAN_EQUAL = "LESS_THAN_EQUAL";
static const string EQUAL_EQUAL = "EQUAL_EQUAL";
static const string NOT_EQUAL = "NOT_EQUAL";
static const string L_PAREN = "L_PAREN";
static const string R_PAREN = "R_PAREN";
static const string L_BRACKET = "L_BRACKET";
static const string R_BRACKET = "R_BRACKET";
static const string L_CURLY_BRACKET = "L_CURLY_BRACKET";
static const string R_CURLY_BRACKET = "R_CURLY_BRACKET";
static const string COLON = "COLON";
static const string COMMA = "COMMA";
static const string DOT = "DOT";
static const string END_OF_FILE = "END_OF_FILE";
static const string STOP_EXPR = "STOP_EXPR";
static const string NUMBERS = "1234567890";
static const string LETTERS = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ";

template<class valueClass>
class Token : public BaseToken {
private:
    /**
     * @tparam valueClass can be any object type that is supported
     */
public:
    Token(string t, valueClass value, int start_pos, int end_pos, int line_num);
    ~Token();

    /**
     * A value of the token if the token type is a supported object type
     * @tparam valueClass
     */
    Value<valueClass> *value;

    /**
     * @tparam valueClass
     * @return Returns the value if the token has one
     */
    Value<valueClass> *getValueObject();

    /**
     * @return Returns the token in readable format
     */
    string toString();

    /**
     * @return Returns the token in readable format
     */
    string toStringNumber();
};


#endif //BOA_T