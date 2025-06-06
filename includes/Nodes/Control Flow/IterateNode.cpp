//
// Created by Preeti Thorat on 1/2/22.
//

#include "IterateNode.h"


IterateNode::IterateNode(Token<string> *iterNameTok, Node *toIterateThrough, Node *body, bool shouldReturnNull)
        : Node(N_ITER) {
    this->iterNameTok = iterNameTok;
    this->toIterateThrough = toIterateThrough;
    this->shouldReturnNull = shouldReturnNull;
    this->body = body;

    posStart = iterNameTok->posStart;
    posEnd = body->posEnd;
}

IterateNode::~IterateNode() {
    delete body;
    delete toIterateThrough;
}

string IterateNode::toString() {
    string str = "(IterateNode: " + iterNameTok->getValueObject()->getValue() + " in " + toIterateThrough->toString() + ", (Body: " + body->toString() + "))";
    return str;
}