//
// Created by Preeti Thorat on 11/26/21.
//

#include "VarAssignNode.h"

VarAssignNode::VarAssignNode(BaseToken *varNameTok, Node *valueNode) : Node(N_VAR_ASSIGN) {
    this->varNameTok = varNameTok;
    this->valueNode = valueNode;
    posStart = valueNode->posStart;
    posEnd = valueNode->posEnd;
    fName = varNameTok->fName;
    fTxt = varNameTok->fTxt;
    line = valueNode->line;
}