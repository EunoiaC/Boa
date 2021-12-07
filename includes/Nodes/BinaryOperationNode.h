//
// Created by Aadi Yadav on 11/7/21.
//

#ifndef BOA_BINARYOPERATIONNODE_H
#define BOA_BINARYOPERATIONNODE_H
#include "NumberNode.h"
#include "Node.h"
#include "../Token/Token.h"
//#include "Node.cpp"

class BinaryOperationNode : public Node {
public:
    Node *left, *right;
    Token<string> * opTok;

    BinaryOperationNode(Node *left, Token<string>* opTok1, Node *right);

    Node *getLeft();

    Node *getRight();

    Token<string> * getOp();

    string toString();
};


#endif //BOA_BINARYOPERATIONNODE_H
