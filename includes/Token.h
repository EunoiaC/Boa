//
// Created by Preeti Thorat on 10/13/21.
//

#ifndef BOA_TOKEN_H
#define BOA_TOKEN_H

#include "Values/Value.cpp"
#include <string>

using namespace std;

template<class valueClass>
class Token {
private:
    /**
     * The type of the token, can be a supported object type, identifier, keyword, or a symbol
     */
    string type;
    /**
     * @tparam valueClass can be any object type that is supported
     */
    /**
     * A value of the token if the token type is a supported object type
     * @tparam valueClass
     */
    Value<valueClass> * value;
public:
    Token(string t, valueClass type);

    Token(string t);
    /**
     * @tparam valueClass
     * @return Returns the value if the token has one
     */
    Value<valueClass>* getValueObject();
};


#endif //BOA_TOKEN_H
