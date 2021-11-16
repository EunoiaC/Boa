//
// Created by Preeti Thorat on 11/7/21.
//

#include "BinaryOperationNode.h"

BinaryOperationNode::BinaryOperationNode(Node *left, Token<string>* opTok1, Node *right) : opTok(opTok1), Node(N_BINOP){
    this->left = left;
    this->right = right;
    this->opTok = opTok1;
}

Node *BinaryOperationNode::getLeft() {
    return this->left;
}

Node *BinaryOperationNode::getRight() {
    return this->right;
}

Token<string> * BinaryOperationNode::getOp() {
    return this->opTok;
}

string BinaryOperationNode::toString() {
    string leftval, rightval;
    leftval = this->left->type == N_BINOP ? ((BinaryOperationNode *) left)->toString()
                                          : to_string(((NumberNode *) left)->token->getValueObject()->getValue());
    rightval = this->right->type == N_BINOP ? ((BinaryOperationNode *) right)->toString()
                                            : to_string(((NumberNode *) right)->token->getValueObject()->getValue());
    return "(" + leftval + " " + this->opTok->type + " " + rightval + ")";
}