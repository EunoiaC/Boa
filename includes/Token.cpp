//
// Created by Preeti Thorat on 10/13/21.
//

#include "Token.h"

Token::Token(string t) {
    type = t;
}

Token::Token(string t, Value<valueClass> v) {
    type = t;
    value = v;
}