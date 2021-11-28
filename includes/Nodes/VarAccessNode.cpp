//
// Created by Preeti Thorat on 11/26/21.
//

#include "VarAccessNode.h"

VarAccessNode::VarAccessNode(BaseToken *varNameTok) : Node(N_VAR_ACCESS){
    this->varNameTok = varNameTok;
    posStart = varNameTok->posStart;
    posEnd = varNameTok->posEnd;
    fName = varNameTok->fName;
    fTxt = varNameTok->fTxt;
    line = varNameTok->line;
}