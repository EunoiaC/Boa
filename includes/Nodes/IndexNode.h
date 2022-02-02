//
// Created by Preeti Thorat on 1/30/22.
//

#ifndef BOA_INDEXNODE_H
#define BOA_INDEXNODE_H

#include "Node.h"
#include <vector>

class IndexNode : public Node {
public:
    vector<Node*> indices;
    Node * left;
    IndexNode(Node *left, vector<Node*> indices);
    ~IndexNode();
    string toString() override;
};


#endif //BOA_INDEXNODE_H
