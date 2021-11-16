//
// Created by Preeti Thorat on 11/15/21.
//

#include "Parser.h"

Parser::Parser(vector<BaseToken *> tokens) {
    this->tokens = tokens;
    this->tokIdx = -1;
    advance();
}

BaseToken *Parser::advance() {
    tokIdx++;
    if (tokIdx < tokens.size()) {
        currentToken = tokens[tokIdx];
    }
    return currentToken;
}

Node *Parser::parse() {
    Node * res = expr();
    return res;
}

Node *Parser::factor() {
    BaseToken *tok = currentToken;
    if (tok->getType() == T_NUM) {
        advance();
        return new NumberNode((Token<double> *) tok);
    }
    return new Node("NULL");
}

Node *Parser::term() {
    return binOp(vector<string>{MULTIPLY, DIVIDE}, &Parser::factor);
}

Node *Parser::expr() {
    return binOp(vector<string>{PLUS, MINUS}, &Parser::term);
}

Node *Parser::binOp(vector<string> ops, Node *(Parser::*func)()) {
    Node *left = factor();
    while (find(ops.begin(), ops.end(), currentToken->getType()) != ops.end()) {
        BaseToken *opTok = currentToken;
        advance();
        Node *right = (this->*func)();
        left = new BinaryOperationNode(left, (Token<string> *) opTok, right);
    }
    return left;
}