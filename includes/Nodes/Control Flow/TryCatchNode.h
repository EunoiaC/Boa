//
// Created by Preeti Thorat on 2/9/22.
//

#ifndef BOA_TRYCATCHNODE_H
#define BOA_TRYCATCHNODE_H

#include "../Node.h"
#include "../../Token/Token.h"


class TryCatchNode : public Node{
public:
    Node * tryBlock, * catchBlock;
    Token<string> * catchName;
    TryCatchNode(Node * tryBlock, Node * catchBlock, Token<string> * catchName);
    string toString() override;
};


#endif //BOA_TRYCATCHNODE_H
