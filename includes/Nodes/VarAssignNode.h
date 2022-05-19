//
// Created by Aadi Yadav on 11/26/21.
//

#ifndef BOA_VARASSIGNNODE_H
#define BOA_VARASSIGNNODE_H
#include "../Token/Token.h"
#include "Node.h"

// Used when assigning to a different type or declaring in a scope
static const string NEW_VALUE = "NEW_VALUE";
// Used when reassigning the value of the variable, like in a statically typed language.
static const string REASSIGN_VAR = "REASSIGN_VAR";

class VarAssignNode : public Node{
public:
    Node *valueNode;
    BaseToken *varNameTok;
    int posStart, posEnd, line;
    string fName, fTxt, assType;
    vector<BaseToken *> parents;
    VarAssignNode(BaseToken *varNameTok, Node *valueNode, vector<BaseToken *> parents, string assType);
    string toString() override;
};


#endif //BOA_VARASSIGNNODE_H
