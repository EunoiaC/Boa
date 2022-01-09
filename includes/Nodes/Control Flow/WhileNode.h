//
// Created by Preeti Thorat on 12/5/21.
//

#ifndef BOA_WHILENODE_H
#define BOA_WHILENODE_H
#include "../Node.h"

class WhileNode : public Node {
public:
    int posStart, posEnd;
    Node *condition, *body;
    bool shouldReturnNull;
    WhileNode(Node *condition, Node *body, bool shouldReturnNull);
    string toString() override;
};


#endif //BOA_WHILENODE_H
