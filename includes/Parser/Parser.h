//
// Created by Aadi Yadav on 11/15/21.
//
#pragma once
#ifndef BOA_PARSER_H
#define BOA_PARSER_H

#include <vector>
#include "../Token/TokenType.h"
#include "../Values/Value.cpp"
#include "../Nodes/BinaryOperationNode.cpp"
#include "../Nodes/UnaryOperationNode.cpp"
#include "../Nodes/VarAccessNode.cpp"
#include "../Nodes/VarAssignNode.cpp"
#include "../Nodes/VarOperationNode.cpp"
//#include "Nodes/NumberNode.cpp"
#include <vector>
#include <fstream>
#include "ParseResult.cpp"

class Parser {
public:
    string fName;
    string currLine;
    vector<string> lines;
    ifstream file;
    Parser(vector<BaseToken *> tokens, string fName, vector<string> lines);
    vector<BaseToken *> tokens;
    int tokIdx;
    BaseToken * currentToken;
    BaseToken * advance();
    ParseResult * factor();
    ParseResult * term();
    ParseResult * expr();
    ParseResult * compExpr();
    ParseResult * arithExpr();
    ParseResult * atom();
    ParseResult * power();
    ParseResult * parse();
    ParseResult * binOp(vector<string> ops, ParseResult *(Parser::*funcA)(), ParseResult *(Parser::*funcB)());
};


#endif //BOA_PARSER_H
