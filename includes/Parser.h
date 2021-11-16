//
// Created by Preeti Thorat on 11/15/21.
//
#pragma once
#ifndef BOA_PARSER_H
#define BOA_PARSER_H

#include <vector>
#include "TokenType.h"
#include "Values/Value.cpp"
#include "Nodes/BinaryOperationNode.cpp"
//#include "Nodes/NumberNode.cpp"
#include <vector>

class Parser {
public:
    Parser(vector<BaseToken *> tokens);
    vector<BaseToken *> tokens;
    int tokIdx;
    BaseToken * currentToken;
    BaseToken * advance();
    Node * factor();
    Node * term();
    Node * expr();
    Node * parse();
    Node * binOp(vector<string> ops, Node *(Parser::*func)());
};


#endif //BOA_PARSER_H
