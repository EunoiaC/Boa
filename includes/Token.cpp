//
// Created by Preeti Thorat on 10/13/21.
//

#include "Token.h"

template<class tokType>
Token<tokType>::Token(string t, tokType v) : BaseToken(t) {
    type = t;
    value = new Value<tokType>(v, t);
}

template<class tokType>
Value<tokType>* Token<tokType>::getValueObject() {
    return value;
}