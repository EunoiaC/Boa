//
// Created by Aadi Yadav on 11/7/21.
//

#include "NumberNode.h"

NumberNode::NumberNode(Token<double> *value) : token(value), Node(N_NUMBER) {
    posStart = value->posStart;
    posEnd = value->posEnd;
    line = token->line;
}

string NumberNode::toString() {
    return to_string(token->getValueObject()->getValue());
}