//
// Created by Preeti Thorat on 10/13/21.
//

#include "Token.h"

template<class v>
Value<v> val;

Token::Token(string t) {
    type = t;
}

template<class valueClass>
Token::Token(string t, Value<valueClass>* v) {
    type = t;
    val<valueClass> = v;
}