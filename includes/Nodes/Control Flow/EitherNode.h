//
// Created by Preeti Thorat on 2/23/22.
//

#ifndef BOA_EITHERNODE_H
#define BOA_EITHERNODE_H

#include "../Node.h"
#include <vector>

class EitherNode : public Node {
public:
    vector<Node *> nodes;
    EitherNode(vector<Node *> nodes);
};


#endif //BOA_EITHERNODE_H
