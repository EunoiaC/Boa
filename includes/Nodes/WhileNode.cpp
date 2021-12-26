//
// Created by Preeti Thorat on 12/5/21.
//

#include "WhileNode.h"

WhileNode::WhileNode(Node *condition, Node *body, bool shouldReturnNull) : Node(N_WHILE){
    this->condition = condition;
    this->body = body;
    this->shouldReturnNull = shouldReturnNull;

    posStart = condition->posStart;
    posEnd = body->posEnd;
}

string WhileNode::toString() {
    string str = "while (" + condition->toString() + ") {\n";
    str += body->toString() + "\n";
    str += "}";
    return str;
}