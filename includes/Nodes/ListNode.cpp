//
// Created by Preeti Thorat on 12/15/21.
//

#include "ListNode.h"

ListNode::ListNode(vector<Node *> elements, int posStart, int posEnd, int line) : Node(N_LIST) {
    this->elements = elements;
    this->posStart = posStart;
    this->posEnd = posEnd;
    this->line = line;
}