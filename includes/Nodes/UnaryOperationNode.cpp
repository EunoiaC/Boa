//
// Created by Preeti Thorat on 11/19/21.
//

#include "UnaryOperationNode.h"

UnaryOperationNode::UnaryOperationNode(Token<string> * op, Node *node) : Node(N_UNOP){
    this->op = op;
    this->node = node;
    posStart = op->posStart;
    posEnd = node->posEnd;
    line = op->line;
}

string UnaryOperationNode::toString() {
    return "(" + op->type + ", " + node->toString() + ")";
}