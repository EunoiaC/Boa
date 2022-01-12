//
// Created by Preeti Thorat on 1/8/22.
//

#include "ReturnNode.h"

ReturnNode::ReturnNode(Node *toReturn, int posStart, int posEnd, int line)  : Node(N_RETURN){
    this->toReturn = toReturn;
    this->posStart = posStart;
    this->posEnd = posEnd;
    this->line = line;
}

string ReturnNode::toString() {
    string result = "ReturnNode: ";
    result += toReturn->toString();
    return result;
}