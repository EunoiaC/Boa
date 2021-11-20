//
// Created by Preeti Thorat on 11/15/21.
//

#include "Parser.h"

Parser::Parser(vector<BaseToken *> tokens, string fName, vector<string> lines) {
    this->lines = lines;
    this->fName = fName;
    this->tokens = tokens;
    file.open(fName);
    this->tokIdx = -1;
    advance();
}

BaseToken *Parser::advance() {
    tokIdx++;
    if (tokIdx < tokens.size()) {
        currentToken = tokens[tokIdx];
        currLine = lines[currentToken->line];
    }
    return currentToken;
}

ParseResult *Parser::parse() {
    ParseResult *res = expr();
    if (!res->error) {
        if (currentToken->getType() != END_OF_FILE && currentToken->getType() != STOP_EXPR) {
            return res->failure(
                    new Error(currentToken->pos_start, currentToken->pos_end, currentToken->line, fName, currLine,
                              "InvalidSyntaxError", "Expected an operation"));
        }
    }
    return res;
}

ParseResult *Parser::factor() {
    ParseResult *res = new ParseResult(nullptr, nullptr);
    BaseToken *tok = currentToken;
    if (tok->getType() == PLUS || tok->getType() == MINUS) {
        advance();
        Node *f = res->reg(factor());
        if (res->error) return res;
        return res->success(new UnaryOperationNode(tok->getType(), (NumberNode *) f));
    } else if (tok->getType() == T_NUM) {
        advance();
        return res->success(new NumberNode((Token<double> *) tok));
    } else if (tok->type == L_PAREN) {
        advance();
        Node *exp = res->reg(expr());
        if (res->error) return res;
        if (currentToken->getType() == R_PAREN) {
            advance();
            return res->success(exp);
        } else {
            return res->failure(
                    new Error(currentToken->pos_start, currentToken->pos_end, currentToken->line, fName, currLine,
                              "InvalidSyntaxError", "Expected a closing parenthesis"));
        }
    }
    return res->failure(new Error(tok->pos_start, tok->pos_end, tok->line, fName, currLine, "InvalidSyntaxError",
                                  "Expected a number"));
}

ParseResult *Parser::term() {
    return binOp(vector<string>{MULTIPLY, DIVIDE}, &Parser::factor);
}

ParseResult *Parser::expr() {
    return binOp(vector<string>{PLUS, MINUS}, &Parser::term);
}

ParseResult *Parser::binOp(vector<string> ops, ParseResult *(Parser::*func)()) {
    ParseResult *res = new ParseResult(nullptr, nullptr);
    Node *left = res->reg((this->*func)());
    if (res->error) return res;
    while (find(ops.begin(), ops.end(), currentToken->getType()) != ops.end()) {
        BaseToken *opTok = currentToken;
        advance();
        Node *right = res->reg((this->*func)());
        if (res->error) return res;
        left = new BinaryOperationNode(left, (Token<string> *) opTok, right);
    }
    return res->success(left);
}