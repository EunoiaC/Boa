//
// Created by Preeti Thorat on 1/8/22.
//

#include "BreakNode.h"

BreakNode::BreakNode(int posStart, int posEnd, int line) : Node(N_BREAK) {
    this->posStart = posStart;
    this->posEnd = posEnd;
    this->line = line;
}