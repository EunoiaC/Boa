//
// Created by Aadi Yadav on 11/26/21.
//

#include "VarAssignNode.h"

VarAssignNode::VarAssignNode(BaseToken *varNameTok, Node *valueNode, vector<BaseToken *> parents, string assType) : Node(N_VAR_ASSIGN) {
    this->varNameTok = varNameTok;
    this->valueNode = valueNode;
    posStart = valueNode->posStart;
    posEnd = valueNode->posEnd;
    fName = varNameTok->fName;
    fTxt = varNameTok->fTxt;
    line = valueNode->line;
    this->assType = assType;
    this->parents = parents;
}

string VarAssignNode::toString() {
    return "Assign: " + varNameTok->toString() + " = " + valueNode->toString();
}