//
// Created by Preeti Thorat on 1/8/22.
//

#ifndef BOA_CONTINUENODE_H
#define BOA_CONTINUENODE_H
#include "../Node.h"

class ContinueNode : public Node {
public:
    int posStart, posEnd, line;
    ContinueNode(int posStart, int posEnd, int line);
};


#endif //BOA_CONTINUENODE_H
