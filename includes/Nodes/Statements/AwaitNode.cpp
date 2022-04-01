//
// Created by Preeti Thorat on 3/30/22.
//

#include "AwaitNode.h"

AwaitNode::AwaitNode(Node *toCall, int posStart, int posEnd, int line) : Node(N_AWAIT) {
    this->toCall = toCall;
    this->posStart = posStart;
    this->posEnd = posEnd;
    this->line = line;
}