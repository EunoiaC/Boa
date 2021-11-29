//
// Created by Preeti Thorat on 11/28/21.
//

#ifndef BOA_VAROPERATIONNODE_H
#define BOA_VAROPERATIONNODE_H


class VarOperationNode : public Node {
public:
    string op;
    BaseToken *var;
    Node *value;
    VarOperationNode(BaseToken *token, Node *node, string operation);
};


#endif //BOA_VAROPERATIONNODE_H
