//
// Created by Preeti Thorat on 11/7/21.
//

#include "BinaryOperationNode.h"

BinaryOperationNode::BinaryOperationNode(Node *left, string operation, Node *right) : Node(N_BINOP){
    this->left = left;
    this->right = right;
    this->op = operation;
}

Node *BinaryOperationNode::getLeft() {
    return this->left;
}

Node *BinaryOperationNode::getRight() {
    return this->right;
}

string BinaryOperationNode::getOp() {
    return this->op;
}