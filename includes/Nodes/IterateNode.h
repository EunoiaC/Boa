//
// Created by Preeti Thorat on 1/2/22.
//

#ifndef BOA_ITERATENODE_H
#define BOA_ITERATENODE_H

#include "Node.h"
#include "../Token/Token.h"

class IterateNode : public Node {
public:
    int posStart, posEnd;
    Token<string> *iterNameTok;
    Node *body, *toIterateThrough;
    bool shouldReturnNull;

    string toString() override;

    IterateNode(Token<string> *iterNameTok, Node *toIterateThrough, Node *body, bool shouldReturnNull);
};


#endif //BOA_ITERATENODE_H
