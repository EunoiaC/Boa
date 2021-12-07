//
// Created by Aadi Yadav on 11/19/21.
//

#ifndef BOA_UNARYOPERATIONNODE_H
#define BOA_UNARYOPERATIONNODE_H
#include "Node.h"
#include "../Token/Token.h"

class UnaryOperationNode : public Node {
public:
    Token<string> *  op;
    Node * node;
    UnaryOperationNode(Token<string> * op, Node * node);
    string toString();
};


#endif //BOA_UNARYOPERATIONNODE_H
