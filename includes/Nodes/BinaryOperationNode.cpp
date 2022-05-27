//
// Created by Aadi Yadav on 11/7/21.
//

#include "BinaryOperationNode.h"

BinaryOperationNode::BinaryOperationNode(Node *left, Token<string>* opTok1, Node *right) : opTok(opTok1), Node(N_BINOP){
    this->left = left;
    this->right = right;
    this->opTok = opTok1;
    posStart = left->posStart;
    posEnd = right->posEnd;
    line = left->line;
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
    leftval = left->toString();
    rightval = right->toString();
    return "(" + leftval + " " + to_string(this->opTok->type) + " " + rightval + ")";
}