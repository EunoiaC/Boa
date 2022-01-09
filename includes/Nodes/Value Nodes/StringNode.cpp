//
// Created by Preeti Thorat on 12/10/21.
//

#include <iostream>
#include "StringNode.h"

StringNode::StringNode(Token<string> *value) : token(value), Node(N_STRING){
    posStart = value->posStart;
    posEnd = value->posEnd;
    line = token->line;
}

string StringNode::toString() {
    return "(STRING:" + token->getValueObject()->val + ")";
}