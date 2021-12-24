//
// Created by Preeti Thorat on 12/4/21.
//
#ifndef BOA_FORNODE_H
#define BOA_FORNODE_H

#include "Node.h"
#include "../Token/Token.h"

class ForNode : public Node {
public:
    int posStart, posEnd;
    Token<string> *varNameTok;
    Node *startVal, *endVal, *body, *stepVal;
    bool shouldReturnNull;
    ForNode(Token<string> *varNameTok, Node *startVal, Node *endVal, Node *stepVal, Node *body, bool shouldReturnNull);
};


#endif //BOA_FORNODE_H
