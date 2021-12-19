//
// Created by Preeti Thorat on 12/18/21.
//

#include "MapNode.h"

MapNode::MapNode(map<Node *, Node *> dict, int posStart, int posEnd, int line) : Node(N_MAP) {
    this->dict = dict;
    this->posStart = posStart;
    this->posEnd = posEnd;
    this->line = line;
}