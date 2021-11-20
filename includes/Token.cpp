//
// Created by Preeti Thorat on 10/13/21.
//

#include "Token.h"

using namespace std;

BaseToken::BaseToken(string t, int start_pos, int end_pos, int line_num) {
    type = t;
    this->fName = fName;
    this->fTxt = fTxt;
    pos_start = start_pos;
    pos_end = end_pos;
    line = line_num;
}

string BaseToken::getType() {
    return type;
}

string BaseToken::posData(){
    return "[" + to_string(pos_start) + ", " + to_string(pos_end) + ", " + to_string(line) + "]";
}

string BaseToken::toString() {
    return type + posData();
}

template<class tokType>
Token<tokType>::Token(string t, tokType v, int start_pos, int end_pos, int line_num) : BaseToken(t, start_pos, end_pos, line_num) {
    type = t;
    value = new Value<tokType>(v, t);
}

template<class tokType>
Value<tokType>* Token<tokType>::getValueObject() {
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