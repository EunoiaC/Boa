//
// Created by Preeti Thorat on 11/26/21.
//

#ifndef BOA_VARACCESSNODE_H
#define BOA_VARACCESSNODE_H


class VarAccessNode : public Node{
public:
    int posStart, posEnd, line;
    string fName, fTxt;
    BaseToken * varNameTok;
    VarAccessNode(BaseToken * varNameTok);
};


#endif //BOA_VARACCESSNODE_H
