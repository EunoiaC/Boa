//
// Created by Preeti Thorat on 11/19/21.
//

#include "UnaryOperationNode.h"

UnaryOperationNode::UnaryOperationNode(string op, Node *node) : Node(N_UNOP){
    this->op = op;
    this->node = node;
}

string UnaryOperationNode::toString() {
    return "(" + op + ", " + node->toString() + ")";
}