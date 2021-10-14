//
// Created by Preeti Thorat on 10/13/21.
//

#ifndef BOA_TOKEN_H
#define BOA_TOKEN_H

#include "Value.cpp"
#include <string>

using namespace std;

class Token {
private:
    /**
     * The type of the token, can be a supported object type, identifier, keyword, or a symbol
     */
    string type;
    /**
     * @tparam valueClass can be any object type that is supported
     */
    template<class valueClass>
    /**
     * A value of the token if the token type is a supported object type
     * @tparam valueClass
     */
    Value<valueClass> value;

public:
    template<class valueClass>
    Token(string t, Value<valueClass> v);

    Token(string t);
};


#endif //BOA_TOKEN_H
