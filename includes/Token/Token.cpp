//
// Created by Aadi Yadav on 10/13/21.
//

#include <iostream>
#include "Token.h"

template<class tokType>
Token<tokType>::Token(string t, tokType v, int start_pos, int end_pos, int line_num) : BaseToken(t, start_pos, end_pos, line_num) {
    type = t;
    value = new Value<tokType>(v, t, fName, fTxt);
}

template<class tokType>
Token<tokType>::~Token() {
    delete value;
}

template<> Token<string>::Token(string t, string v, int start_pos, int end_pos, int line_num) : BaseToken(t, start_pos, end_pos, line_num) {
    type = t;
    value = new String<string>(v, fName, fTxt);
}

template<> Token<double>::Token(string t, double v, int start_pos, int end_pos, int line_num) : BaseToken(t, start_pos, end_pos, line_num) {
    type = t;
    value = new Number<double>(v, fName, fTxt);
}



template<class valueClass>
Value<valueClass> *Token<valueClass>::getValueObject() {
    return value;
}

template<class tokType>
string Token<tokType>::toStringNumber() {
    return type + ":" + to_string(value->getValue()) + posData();
}

template<> Value<double> *Token<double>::getValueObject() {
    return value;
}

template<> Value<string> *Token<string>::getValueObject() {
    return value;
}

template<class tokType>
string Token<tokType>::toString() {
    return type; // + ":" + value->getValue();
}