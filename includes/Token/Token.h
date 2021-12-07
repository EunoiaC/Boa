//
// Created by Aadi Yadav on 10/13/21.
//

#ifndef BOA_TOKEN_H
#define BOA_TOKEN_H

#include "../Values/Value.h"

using namespace std;

class BaseToken{
public:
    string fName, fTxt;
    BaseToken(string t, int start_pos, int end_pos, int line_num);
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
    string type;
    /**
     * @return The type of token
     */
     string getType();
    /**
     * @return Type of the Token
     */
    string toString();
    /**
     * @return Position data of the Token
     */
    string posData();
};

template<class valueClass>
class Token : public BaseToken{
private:
    /**
     * @tparam valueClass can be any object type that is supported
     */
    /**
     * A value of the token if the token type is a supported object type
     * @tparam valueClass
     */
    Value<valueClass> * value;
public:
    Token(string t, valueClass value, int start_pos, int end_pos, int line_num);
    /**
     * @tparam valueClass
     * @return Returns the value if the token has one
     */
    Value<valueClass>* getValueObject();
    /**
     * @return Returns the token in readable format
     */
    string toString();
    /**
     * @return Returns the token in readable format
     */
    string toStringNumber();
};


#endif //BOA_TOKEN_H
