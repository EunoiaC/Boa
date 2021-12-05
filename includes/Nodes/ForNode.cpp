//
// Created by Preeti Thorat on 12/4/21.
//

#include "ForNode.h"

ForNode::ForNode(Token<string> *varNameTok, Node *startVal, Node *endVal, Node *stepVal, Node *body) : Node(N_FOR) {
    this->varNameTok = varNameTok;
    this->startVal = startVal;
    this->endVal = endVal;
    this->stepVal = stepVal;
    this->body = body;

    posStart = varNameTok->posStart;
    posEnd = body->posEnd;
}