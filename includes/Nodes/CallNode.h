//
// Created by Preeti Thorat on 12/5/21.
//

#ifndef BOA_CALLNODE_H
#define BOA_CALLNODE_H
#include "Node.h"
#include <vector>

class CallNode : public Node {
public:
    Node * nodeToCall;
    vector<Node *> args;
    int posStart, posEnd;
    CallNode(Node * nodeToCall, vector<Node*> args);
    string toString() override;
};


#endif //BOA_CALLNODE_H
