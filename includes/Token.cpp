//
// Created by Preeti Thorat on 10/6/21.
//

#include "Token.h"

Token::Token(Value value, string valType) {
    val = value;
    type = valType;
}

string Token::toString() {
    return to_string(val) + ":" + type;
}
