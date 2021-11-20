//
// Created by Preeti Thorat on 11/19/21.
//

#ifndef BOA_UNARYOPERATIONNODE_H
#define BOA_UNARYOPERATIONNODE_H

class UnaryOperationNode : public Node {
public:
    string op;
    Node * node;
    UnaryOperationNode(string op, Node * node);
    string toString();
};


#endif //BOA_UNARYOPERATIONNODE_H
