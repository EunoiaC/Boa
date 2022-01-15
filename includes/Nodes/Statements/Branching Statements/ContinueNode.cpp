//
// Created by Preeti Thorat on 1/8/22.
//

#include "ContinueNode.h"

ContinueNode::ContinueNode(int posStart, int posEnd, int line) : Node(N_CONTINUE) {
    this->posStart = posStart;
    this->posEnd = posEnd;
    this->line = line;
}