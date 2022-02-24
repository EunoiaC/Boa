//
// Created by Preeti Thorat on 2/23/22.
//

#ifndef BOA_EITHERNODE_H
#define BOA_EITHERNODE_H

#include "../Node.h"

class EitherNode : public Node {
public:
    Node * first, * second;
    EitherNode(Node * first, Node * second);
};


#endif //BOA_EITHERNODE_H
