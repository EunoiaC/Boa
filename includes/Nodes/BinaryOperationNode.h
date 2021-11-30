//
// Created by Aadi Yadav on 11/7/21.
//
#pragma once
#ifndef BOA_BINARYOPERATIONNODE_H
#define BOA_BINARYOPERATIONNODE_H
#include "NumberNode.cpp"
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
