//
// Created by Preeti Thorat on 12/4/21.
//
#ifndef BOA_FORNODE_H
#define BOA_FORNODE_H

#include "Node.cpp"
#include "../Token/Token.cpp"

class ForNode : public Node {
public:
    int posStart, posEnd;
    Token<string> *varNameTok;
    Node *startVal, *endVal, *body, *stepVal;
    ForNode(Token<string> *varNameTok, Node *startVal, Node *endVal, Node *stepVal, Node *body);
};


#endif //BOA_FORNODE_H
