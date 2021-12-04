//
// Created by Aadi Yadav on 11/15/21.
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
                    new Error(currentToken->posStart, currentToken->posEnd, currentToken->line, fName, currLine,
                              "InvalidSyntaxError", "Expected an operation"));
        }
    }
    return res;
}

ParseResult *Parser::atom() {
    ParseResult *res = new ParseResult(nullptr, nullptr);
    BaseToken *tok = currentToken;

    if (tok->getType() == T_NUM) {
        res->regAdvancement();
        advance();
        return res->success(new NumberNode((Token<double> *) tok));
    } else if (tok->getType() == IDENTIFIER) {
        res->regAdvancement();
        advance();
        string type = currentToken->getType();
        //If the token is equal, we assign a new variable to the node
        if (type == EQUAL) {
            res->regAdvancement();
            advance();
            Node *exp = res->reg(expr());
            if (res->error) return res;
            return res->success(new VarAssignNode((Token<string> *) tok, exp));
        } else if (type == PLUS_EQUAL || type == MINUS_EQUAL) {
            res->regAdvancement();
            advance();
            Node *exp = res->reg(expr());
            if (res->error) return res;
            return res->success(new VarOperationNode((Token<string> *) tok, exp, type));
        } else if (type == PLUS_PLUS || type == MINUS_MINUS) {
            res->regAdvancement();
            advance();
            return res->success(new VarOperationNode((Token<string> *) tok, nullptr, type));
        }
        return res->success(new VarAccessNode((Token<string> *) tok));
    } else if (tok->getType() == L_PAREN) {
        res->regAdvancement();
        advance();
        Node *exp = res->reg(expr());
        if (res->error) return res;
        if (currentToken->getType() == R_PAREN) {
            res->regAdvancement();
            advance();
            return res->success(exp);
        } else {
            return res->failure(
                    new Error(currentToken->posStart, currentToken->posEnd, currentToken->line, fName, currLine,
                              "InvalidSyntaxError", "Expected a closing parenthesis"));
        }
    }

    return res->failure(new Error(tok->posStart, tok->posEnd, tok->line, fName, currLine, "InvalidSyntaxError",
                                  "Expected a number, variable, operation, or '('"));

}

ParseResult *Parser::factor() {
    ParseResult *res = new ParseResult(nullptr, nullptr);
    BaseToken *tok = currentToken;
    if (tok->getType() == PLUS || tok->getType() == MINUS) {
        res->regAdvancement();
        advance();
        Node *f = res->reg(factor());
        if (res->error) return res;
        return res->success(new UnaryOperationNode((Token<string> *) tok, (NumberNode *) f));
    }
    return power();
}

ParseResult *Parser::power() {
    return binOp({POWER}, &Parser::atom, &Parser::factor);
}

ParseResult *Parser::term() {
    return binOp({MULTIPLY, DIVIDE, MOD}, &Parser::factor, &Parser::factor);
}

ParseResult *Parser::compExpr() {
    ParseResult *res = new ParseResult(nullptr, nullptr);
    Node *node;

    if (currentToken->getType() == NOT) {
        auto opTok = currentToken;
        res->regAdvancement();
        advance();
        node = res->reg(compExpr());
        if (res->error) return res;
        return res->success(new UnaryOperationNode((Token<string> *) opTok, node));
    }

    node = res->reg(
            binOp({EQUAL_EQUAL, GREATER_THAN, LESS_THAN, LESS_THAN_EQUAL, GREATER_THAN_EQUAL, NOT_EQUAL}, &Parser::arithExpr,
                  &Parser::arithExpr));
    if (res->error)
        return res->failure(
                new Error(currentToken->posStart, currentToken->posEnd, currentToken->line, fName, currLine,
                          "InvalidSyntaxError", "Expected a number, identifier, operation, '(', 'NOT' "));
    return res->success(node);

}

ParseResult *Parser::arithExpr() {
    return binOp({PLUS, MINUS}, &Parser::term, &Parser::term);
}

ParseResult *Parser::expr() {
    ParseResult *res = new ParseResult(nullptr, nullptr);
    Node *node = res->reg(binOp({AND, OR}, &Parser::compExpr, &Parser::compExpr));
    if (res->error)
        return res->failure(
                new Error(currentToken->posStart, currentToken->posEnd, currentToken->line, fName, currLine,
                          "InvalidSyntaxError", "Expected an operation, identifier, number, or '('"));
    return res->success(node);
}

ParseResult *Parser::binOp(vector<string> ops, ParseResult *(Parser::*funcA)(), ParseResult *(Parser::*funcB)()) {
    ParseResult *res = new ParseResult(nullptr, nullptr);
    Node *left = res->reg((this->*funcA)());
    if (res->error) return res;
    while (find(ops.begin(), ops.end(), currentToken->getType()) != ops.end()) {
        BaseToken *opTok = currentToken;
        res->regAdvancement();
        advance();
        Node *right = res->reg((this->*funcB)());
        if (res->error) return res;
        left = new BinaryOperationNode(left, (Token<string> *) opTok, right);
    }
    return res->success(left);
}