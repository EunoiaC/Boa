//
// Created by Preeti Thorat on 11/7/21.
//
#pragma once
#ifndef BOA_BINARYOPERATIONNODE_H
#define BOA_BINARYOPERATIONNODE_H
#include "Node.cpp"

class BinaryOperationNode : public Node {
public:
    Node *left, *right;
    string op;

    BinaryOperationNode(Node *left, string op, Node *right);

    Node *getLeft();

    Node *getRight();

    string getOp();
};


#endif //BOA_BINARYOPERATIONNODE_H
