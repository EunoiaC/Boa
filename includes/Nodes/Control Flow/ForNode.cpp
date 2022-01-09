//
// Created by Preeti Thorat on 12/4/21.
//

#include "ForNode.h"

ForNode::ForNode(Token<string> *varNameTok, Node *startVal, Node *endVal, Node *stepVal, Node *body, bool shouldReturnNull) : Node(N_FOR) {
    this->varNameTok = varNameTok;
    this->startVal = startVal;
    this->endVal = endVal;
    this->stepVal = stepVal;
    this->body = body;
    this->shouldReturnNull = shouldReturnNull;

    line = varNameTok->line;
    posStart = varNameTok->posStart;
    posEnd = body->posEnd;
}

string ForNode::toString() {
    string str = "for " + varNameTok->getValueObject()->getValue() + " in " + startVal->toString() + " to " + endVal->toString();
    if (stepVal != nullptr) {
        str += " step " + stepVal->toString();
    }
    str += " do " + body->toString();
    return str;
}