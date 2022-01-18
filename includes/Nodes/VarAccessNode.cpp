//
// Created by Aadi Yadav on 11/26/21.
//

#include "VarAccessNode.h"

#include <utility>

VarAccessNode::VarAccessNode(Token<string> *varNameTok, vector<BaseToken*> identifiers) : Node(N_VAR_ACCESS){
    this->varNameTok = varNameTok;
    this->identifiers = move(identifiers);
    posStart = varNameTok->posStart;
    posEnd = varNameTok->posEnd;
    fName = varNameTok->fName;
    fTxt = varNameTok->fTxt;
    line = varNameTok->line;
}

string VarAccessNode::toString() {
    return "(VarAccessNode: " + varNameTok->getValueObject()->getValue() + ")";
}