//
// Created by Preeti Thorat on 12/4/21.
//

#ifndef BOA_IFNODE_H
#define BOA_IFNODE_H
#include "../Node.h"
#include <vector>
#include <tuple>

class IfNode : public Node {
public:
    Node * elseCase;
    int posStart, posEnd;
    vector<tuple<Node *, Node *>> cases;
    IfNode(vector<tuple<Node *, Node *>> cases, Node * elseCase);
    ~IfNode();
    string toString() override;
};


#endif //BOA_IFNODE_H
