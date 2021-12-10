//
// Created by Preeti Thorat on 12/5/21.
//

#include "CallNode.h"

CallNode::CallNode(Node *nodeToCall, vector<Node *> args) : Node(N_CALL){
    this->nodeToCall = nodeToCall;
    this->args = args;

    posStart = nodeToCall->posStart;

    if(args.size() > 0){
        posEnd = args[args.size() - 1]->posEnd;
    }
    else{
        posEnd = nodeToCall->posEnd;
    }
}

string CallNode::toString() {
    return "(CallNode: " + nodeToCall->toString() + ")";
}