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
    VarAccessNode(Token<string> * varNameTok);
};


#endif //BOA_VARACCESSNODE_H
