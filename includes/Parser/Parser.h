//
// Created by Aadi Yadav on 11/15/21.
//

#ifndef BOA_PARSER_H
#define BOA_PARSER_H

#include <vector>
#include "../Nodes/ForNode.h"
#include "../Nodes/WhileNode.h"
#include "../Nodes/FuncDefNode.h"
#include "../Nodes/CallNode.h"
#include "../Values/Value.h"
#include "../Nodes/BinaryOperationNode.h"
#include "../Nodes/IfNode.h"
#include "../Nodes/UnaryOperationNode.h"
#include "../Nodes/VarAccessNode.h"
#include "../Nodes/VarAssignNode.h"
#include "../Nodes/VarOperationNode.h"
#include <vector>
#include <fstream>
#include "ParseResult.h"

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
    ParseResult * ifExpr();
    ParseResult * forExpr();
    ParseResult * whileExpr();
    ParseResult * funcDef();
    ParseResult * binOp(vector<string> ops, ParseResult *(Parser::*funcA)(), ParseResult *(Parser::*funcB)());
};


#endif //BOA_PARSER_H
