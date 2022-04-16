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

ListNode::~ListNode() {
}

string ListNode::toString() {
    string str = "";
    for (int i = 0; i < elements.size(); i++) {
        str += elements[i]->toString();
    }
    return str;
}