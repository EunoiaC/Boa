//
// Created by Aadi Yadav on 11/26/21.
//

#include "VarAccessNode.h"

#include <utility>

VarAccessNode::VarAccessNode(Token<string> *varNameTok, vector<BaseToken*> identifiers, Node * toGetIdentifierFrom) : Node(N_VAR_ACCESS){
    this->varNameTok = varNameTok;
    this->identifiers = move(identifiers);
    this->toGetIdentifierFrom = toGetIdentifierFrom;
    posStart = varNameTok ? varNameTok->posStart : toGetIdentifierFrom->posStart;
    posEnd = varNameTok ?varNameTok->posEnd : toGetIdentifierFrom->posEnd;
    fName = varNameTok ? varNameTok->fName : toGetIdentifierFrom->fName;
    fTxt = (varNameTok ? varNameTok->fTxt : toGetIdentifierFrom->fTxt);
    line = varNameTok ? varNameTok->line : toGetIdentifierFrom->line;
}

string VarAccessNode::toString() {
    return "(VarAccessNode: " + varNameTok->toString() + ")";
}