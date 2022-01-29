//
// Created by Aadi Yadav on 11/15/21.
//

#ifndef BOA_PARSER_H
#define BOA_PARSER_H

#include <vector>
#include "../Nodes/Control Flow/ForNode.h"
#include "../Nodes/Control Flow/IterateNode.h"
#include "../Nodes/Value Nodes/ListNode.h"
#include "../Nodes/Value Nodes/StringNode.h"
#include "../Nodes/Control Flow/WhileNode.h"
#include "../Nodes/Control Flow/FuncDefNode.h"
#include "../Nodes/CallNode.h"
#include "../Values/BaseValues/Value.h"
#include "../Nodes/BinaryOperationNode.h"
#include "../Nodes/Control Flow/IfNode.h"
#include "../Nodes/UnaryOperationNode.h"
#include "../Nodes/VarAccessNode.h"
#include "../Nodes/VarAssignNode.h"
#include "../Nodes/Statements/Branching Statements/ReturnNode.h"
#include "../Nodes/Statements/Branching Statements/ContinueNode.h"
#include "../Nodes/Statements/Branching Statements/BreakNode.h"
#include "../Nodes/Statements/ImportNode.h"
#include "../Nodes/Value Nodes/MapNode.h"
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
    int line;
    Error * priorityError;
    Node * toCall;
    bool reversing = false;

    BaseToken * currentToken;
    BaseToken * advance();
    BaseToken * reverse(int amnt);
    void updateCurrentTok();
    void checkNewLines();
    bool checkNewLinesTo(string type);

    ParseResult * factor();
    ParseResult * term();
    ParseResult * statement();
    ParseResult * statements();
    ParseResult * expr();
    ParseResult * compExpr();
    ParseResult * arithExpr();
    ParseResult * atom();
    ParseResult * power();
    ParseResult * call();
    ParseResult * parse();
    ParseResult * listExpr();
    ParseResult * mapExpr();
    ParseResult * ifExpr();
    ParseResult * forExpr();
    ParseResult * iterExprA();
    ParseResult * iterExprB(Token<string> * varName);
    ParseResult * whileExpr();
    ParseResult * funcDef();
    ParseResult * binOp(vector<string> ops, ParseResult *(Parser::*funcA)(), ParseResult *(Parser::*funcB)());
};


#endif //BOA_PARSER_H
