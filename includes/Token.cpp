//
// Created by Preeti Thorat on 10/13/21.
//

#include "Token.h"

template<class tokType>
Token<tokType>::Token(string t, Value<tokType>* v) {
    type = t;
    value = v;
}

template<class tokType>
Value<tokType>* Token<tokType>::getValueObject() {
    return value;
}