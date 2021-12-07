//
// Created by Aadi Yadav on 10/13/21.
//

#include "Token.h"

template<class tokType>
Token<tokType>::Token(string t, tokType v, int start_pos, int end_pos, int line_num) : BaseToken(t, start_pos, end_pos, line_num) {
    type = t;
    value = new Value<tokType>(v, t, fName, fTxt);
}

template<class valueClass>
Value<valueClass> *Token<valueClass>::getValueObject() {
    return value;
}

template<class tokType>
string Token<tokType>::toStringNumber() {
    return type + ":" + to_string(value->getValue()) + posData();
}

template<class tokType>
string Token<tokType>::toString() {
    return type + ":" + value->getValue();
}