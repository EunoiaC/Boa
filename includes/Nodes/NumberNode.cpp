//
// Created by Preeti Thorat on 11/7/21.
//

#include "NumberNode.h"

NumberNode::NumberNode(Token<double> *value) : token(value), Node(N_NUMBER) {
    token = value;
}

string NumberNode::toString() {
    return token->toStringNumber();
}