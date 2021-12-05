//
// Created by Preeti Thorat on 12/5/21.
//

#include "WhileNode.h"

WhileNode::WhileNode(Node *condition, Node *body) : Node(N_WHILE){
    this->condition = condition;
    this->body = body;

    posStart = condition->posStart;
    posEnd = body->posEnd;
}