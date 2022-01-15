//
// Created by Preeti Thorat on 1/8/22.
//

#ifndef BOA_RETURNNODE_H
#define BOA_RETURNNODE_H

#include "../../Node.h"

class ReturnNode : public Node {
public:
    Node * toReturn;
    int posStart, posEnd, line;
    ReturnNode(Node *toReturn, int posStart, int posEnd, int line);

    string toString() override;
};


#endif //BOA_RETURNNODE_H
