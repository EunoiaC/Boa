//
// Created by Preeti Thorat on 12/5/21.
//

#ifndef BOA_WHILENODE_H
#define BOA_WHILENODE_H
#include "Node.h"

class WhileNode : public Node {
public:
    int posStart, posEnd;
    Node *condition, *body;
    WhileNode(Node *condition, Node *body);
};


#endif //BOA_WHILENODE_H
