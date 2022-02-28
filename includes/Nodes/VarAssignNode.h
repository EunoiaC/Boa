//
// Created by Aadi Yadav on 11/26/21.
//

#ifndef BOA_VARASSIGNNODE_H
#define BOA_VARASSIGNNODE_H
#include "../Token/Token.h"
#include "Node.h"

class VarAssignNode : public Node{
public:
    Node *valueNode;
    BaseToken *varNameTok;
    int posStart, posEnd, line;
    string fName, fTxt;
    vector<BaseToken *> parents;
    VarAssignNode(BaseToken *varNameTok, Node *valueNode, vector<BaseToken *> parents);
    string toString() override;
};


#endif //BOA_VARASSIGNNODE_H
