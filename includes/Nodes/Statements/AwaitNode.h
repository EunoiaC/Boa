//
// Created by Preeti Thorat on 3/30/22.
//

#ifndef BOA_AWAITNODE_H
#define BOA_AWAITNODE_H


#include "../Node.h"
#include "../../Token/Token.h"

class AwaitNode : public Node {
public:
    Node * toCall;
    int posStart, posEnd, line;
    AwaitNode(Node *toCall, int posStart, int posEnd, int line);
};


#endif //BOA_AWAITNODE_H
