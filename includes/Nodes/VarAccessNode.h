//
// Created by Aadi Yadav on 11/26/21.
//

#ifndef BOA_VARACCESSNODE_H
#define BOA_VARACCESSNODE_H
#include "../Token/Token.h"
#include "Node.h"

class VarAccessNode : public Node{
public:
    int posStart, posEnd, line;
    string toString() override;
    string fName, fTxt;
    Token<string> * varNameTok;
    Node * toGetIdentifierFrom;
    vector<BaseToken*> identifiers;
    VarAccessNode(Token<string> * varNameTok, vector<BaseToken*> identifiers, Node * toGetIdentifierFrom);
};


#endif //BOA_VARACCESSNODE_H
