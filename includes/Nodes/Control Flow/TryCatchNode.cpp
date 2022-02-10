//
// Created by Preeti Thorat on 2/9/22.
//

#include "TryCatchNode.h"

TryCatchNode::TryCatchNode(Node *tryBlock, Node *catchBlock, Token<string> * catchName) : Node(N_TRY_CATCH) {
    this->tryBlock = tryBlock;
    this->catchBlock = catchBlock;
    this->catchName = catchName;
}

string TryCatchNode::toString() {
    return "(Try: " + tryBlock->toString() + " Catch: " + catchBlock->toString() + ")";
}