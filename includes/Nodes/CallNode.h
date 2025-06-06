//
// Created by Preeti Thorat on 12/5/21.
//

#ifndef BOA_CALLNODE_H
#define BOA_CALLNODE_H
#include "Node.h"
#include "VarAccessNode.h"
#include <vector>

class CallNode : public Node {
public:
    Node * nodeToCall;
    vector<Node *> args;
    map<VarAccessNode *, Node *> kwargs;
    int posStart, posEnd;
    CallNode(Node * nodeToCall, vector<Node*> args, map<VarAccessNode *, Node *> kwargs = {});
    ~CallNode();
    string toString() override;
};


#endif //BOA_CALLNODE_H
