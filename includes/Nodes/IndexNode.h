//
// Created by Preeti Thorat on 1/30/22.
//

#ifndef BOA_INDEXNODE_H
#define BOA_INDEXNODE_H

#include "Node.h"
#include <vector>

static const string SET_VALUE = "SET_VALUE";
static const string GET_VALUE = "GET_VALUE";

class IndexNode : public Node {
public:
    vector<Node*> indices;
    Node * left;
    string type;
    Node * newVal;
    IndexNode(Node *left, vector<Node*> indices, string type);
    ~IndexNode();
    string toString() override;
};


#endif //BOA_INDEXNODE_H
