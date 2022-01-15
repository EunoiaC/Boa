//
// Created by Preeti Thorat on 1/14/22.
//

#include "ImportNode.h"

ImportNode::ImportNode(Node *toImport, int posStart, int posEnd, int line)  : Node(N_IMPORT){
    this->toImport = toImport;
    this->posStart = posStart;
    this->posEnd = posEnd;
    this->line = line;
}