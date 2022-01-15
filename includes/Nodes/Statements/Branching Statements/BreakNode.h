//
// Created by Preeti Thorat on 1/8/22.
//

#ifndef BOA_BREAKNODE_H
#define BOA_BREAKNODE_H
#include "../../Node.h"

class BreakNode : public Node {
public:
    int posStart, posEnd, line;
    BreakNode(int posStart, int posEnd, int line);
};

#endif //BOA_BREAKNODE_H
