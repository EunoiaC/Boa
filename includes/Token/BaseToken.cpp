//
// Created by Preeti Thorat on 12/6/21.
//

#include "BaseToken.h"
#include <iostream>


BaseToken::BaseToken(TOK_TYPE t, int start_pos, int end_pos, int line_num) {
    type = t;
    this->fName = fName;
    this->fTxt = fTxt;
    posStart = start_pos;
    posEnd = end_pos;
    line = line_num;
}

BaseToken::~BaseToken() {
}

BaseToken::TOK_TYPE BaseToken::getType() {
    return type;
}

string BaseToken::posData(){
    return "[" + to_string(posStart) + ", " + to_string(posEnd) + ", " + to_string(line) + "]";
}

string BaseToken::toString() {
    return to_string(type) + posData();
}