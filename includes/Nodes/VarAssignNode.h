//
// Created by Preeti Thorat on 11/26/21.
//

#ifndef BOA_VARASSIGNNODE_H
#define BOA_VARASSIGNNODE_H


class VarAssignNode : public Node{
public:
    Node *valueNode;
    BaseToken *varNameTok;
    int posStart, posEnd, line;
    string fName, fTxt;
    VarAssignNode(BaseToken *varNameTok, Node *valueNode);
};


#endif //BOA_VARASSIGNNODE_H
