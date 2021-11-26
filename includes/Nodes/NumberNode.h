//
// Created by Preeti Thorat on 11/7/21.
//
#pragma once
#ifndef BOA_NUMBERNODE_H
#define BOA_NUMBERNODE_H
#include "Node.cpp"
#include "../Token/Token.cpp"

class NumberNode : public Node {
public:
    NumberNode(Token<double> *value);
    /**
     * Value of the node
     */
    Token<double> *token;
    string toString();
};


#endif //BOA_NUMBERNODE_H
