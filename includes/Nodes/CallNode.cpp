//
// Created by Preeti Thorat on 12/5/21.
//

#include "CallNode.h"
#include "VarAccessNode.h"

CallNode::CallNode(Node *nodeToCall, vector<Node *> args) : Node(N_CALL){
    this->nodeToCall = nodeToCall;
    this->args = args;

    posStart = ((VarAccessNode *) nodeToCall)->posStart;
    fTxt = ((VarAccessNode *) nodeToCall)->fTxt;

    if(args.size() > 0){
        posEnd = args[args.size() - 1]->posEnd;
    }
    else{
        posEnd = ((VarAccessNode *) nodeToCall)->posEnd;
    }
}

CallNode::~CallNode(){
    delete nodeToCall;
    for(int i = 0; i < args.size(); i++){
        delete args[i];
    }
}

string CallNode::toString() {
    return "(CallNode: " + nodeToCall->toString() + ")";
}