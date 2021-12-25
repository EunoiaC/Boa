//
// Created by Aadi Yadav on 11/15/21.
//

#include <iostream>
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
    updateCurrentTok();
    return currentToken;
}

BaseToken *Parser::reverse(int amnt) {
    tokIdx -= amnt;
    updateCurrentTok();
    return currentToken;
}

void Parser::updateCurrentTok() {
    if (tokIdx >= 0 && tokIdx < tokens.size()) {
        currentToken = tokens[tokIdx];
        currLine = lines[currentToken->line];
    }
}

ParseResult *Parser::parse() {
    ParseResult *res = statements();
    if (!res->error) {
        if (currentToken->getType() != END_OF_FILE && currentToken->getType() != STOP_EXPR) {
            return res->failure(
                    new Error(currentToken->posStart, currentToken->posEnd, currentToken->line, fName, currLine,
                              "InvalidSyntaxError", "Expected an operation"));
        }
    }
    return res;
}

ParseResult *Parser::ifExpr() {
    ParseResult *res = new ParseResult(nullptr, nullptr);
    Node *elseCase = nullptr;
    vector<tuple<Node *, Node *>> cases;
    if (currentToken->getType() != IF) {
        return res->failure(
                new Error(currentToken->posStart, currentToken->posEnd, currentToken->line, fName, currLine,
                          "InvalidSyntaxError", "Expected 'if'"));
    }
    res->regAdvancement();
    advance();
    Node *condition = res->reg(expr());
    if (res->error) return res;
    if (currentToken->getType() != DO) {
        return res->failure(
                new Error(currentToken->posStart, currentToken->posEnd, currentToken->line, fName, currLine,
                          "InvalidSyntaxError", "Expected 'do'"));
    }
    res->regAdvancement();
    advance();
    Node *exp = res->reg(expr());
    if (res->error) return res;
    cases.push_back(make_tuple(condition, exp));

    while (currentToken->getType() == ELIF) {
        res->regAdvancement();
        advance();

        condition = res->reg(expr());
        if (res->error) return res;

        if (currentToken->getType() != DO) {
            return res->failure(
                    new Error(currentToken->posStart, currentToken->posEnd, currentToken->line, fName, currLine,
                              "InvalidSyntaxError", "Expected 'do'"));
        }

        res->regAdvancement();
        advance();
        exp = res->reg(expr());

        if (res->error) return res;
        cases.push_back(make_tuple(condition, exp));
    }
    if (currentToken->getType() == ELSE) {
        res->regAdvancement();
        advance();
        elseCase = res->reg(expr());
        if (res->error) return res;
    }
    return res->success(new IfNode(cases, elseCase));
}

ParseResult *Parser::forExpr() {
    ParseResult *res = new ParseResult(nullptr, nullptr);

    if (currentToken->getType() != FOR) {
        return res->failure(
                new Error(currentToken->posStart, currentToken->posEnd, currentToken->line, fName, currLine,
                          "InvalidSyntaxError", "Expected 'for'"));
    }
    res->regAdvancement();
    advance();
    if (currentToken->getType() != IDENTIFIER) {
        return res->failure(
                new Error(currentToken->posStart, currentToken->posEnd, currentToken->line, fName, currLine,
                          "InvalidSyntaxError", "Expected identifier"));
    }

    Token<string> *identifier = (Token<string> *) currentToken;
    res->regAdvancement();
    advance();

    if (currentToken->getType() != EQUAL) {
        return res->failure(
                new Error(currentToken->posStart, currentToken->posEnd, currentToken->line, fName, currLine,
                          "InvalidSyntaxError", "Expected '='"));
    }

    res->regAdvancement();
    advance();

    Node *startVal = res->reg(expr());
    if (res->error) return res;

    if (currentToken->getType() != TO) {
        return res->failure(
                new Error(currentToken->posStart, currentToken->posEnd, currentToken->line, fName, currLine,
                          "InvalidSyntaxError", "Expected 'to'"));
    }

    res->regAdvancement();
    advance();

    Node *endVal = res->reg(expr());
    if (res->error) return res;

    Node *changeVal = nullptr;

    if (currentToken->getType() == CHGBY) {
        res->regAdvancement();
        advance();
        changeVal = res->reg(expr());
        if (res->error) return res;
    }

    if (currentToken->getType() != DO) {
        return res->failure(
                new Error(currentToken->posStart, currentToken->posEnd, currentToken->line, fName, currLine,
                          "InvalidSyntaxError", "Expected 'do' or 'chgby'"));
    }

    res->regAdvancement();
    advance();

    if(currentToken->getType() == L_CURLY_BRACKET){
        res->regAdvancement();
        advance();

        if(currentToken->getType() == STOP_EXPR) {
            Node *body = res->reg(statements());
            if (res->error) return res;

            if (currentToken->getType() != R_CURLY_BRACKET) {
                return res->failure(
                        new Error(currentToken->posStart, currentToken->posEnd, currentToken->line, fName, currLine,
                                  "InvalidSyntaxError", "Expected '}'"));
            }

            res->regAdvancement();
            advance();

            return res->success(new ForNode(identifier, startVal, endVal, changeVal, body, true));
        }
    }

    Node *body = res->reg(expr());
    if (res->error) return res;

    return res->success(new ForNode(identifier, startVal, endVal, changeVal, body, false));
}

ParseResult *Parser::whileExpr() {
    ParseResult *res = new ParseResult(nullptr, nullptr);
    if (currentToken->getType() != WHILE) {
        return res->failure(
                new Error(currentToken->posStart, currentToken->posEnd, currentToken->line, fName, currLine,
                          "InvalidSyntaxError", "Expected 'while'"));
    }

    res->regAdvancement();
    advance();

    Node *condition = res->reg(expr());
    if (res->error) return res;

    if (currentToken->getType() != DO) {
        return res->failure(
                new Error(currentToken->posStart, currentToken->posEnd, currentToken->line, fName, currLine,
                          "InvalidSyntaxError", "Expected 'do' or 'chgby'"));
    }

    res->regAdvancement();
    advance();

    if(currentToken->getType() == L_CURLY_BRACKET){
        res->regAdvancement();
        advance();

        if(currentToken->getType() == STOP_EXPR) {
            Node *body = res->reg(statements());
            if (res->error) return res;

            if (currentToken->getType() != R_CURLY_BRACKET) {
                return res->failure(
                        new Error(currentToken->posStart, currentToken->posEnd, currentToken->line, fName, currLine,
                                  "InvalidSyntaxError", "Expected '}'"));
            }

            res->regAdvancement();
            advance();

            return res->success(new WhileNode(condition, body, true));
        }
    }

    Node *body = res->reg(expr());
    if (res->error) return res;

    return res->success(new WhileNode(condition, body, false));
}

ParseResult *Parser::funcDef() {
    ParseResult *res = new ParseResult(nullptr, nullptr);
    if (currentToken->getType() != OP) {
        return res->failure(
                new Error(currentToken->posStart, currentToken->posEnd, currentToken->line, fName, currLine,
                          "InvalidSyntaxError", "Expected 'op'"));
    }

    res->regAdvancement();
    advance();
    Token<string> *varNameTok = nullptr;
    if (currentToken->getType() == IDENTIFIER) {
        varNameTok = (Token<string> *) currentToken;
        res->regAdvancement();
        advance();
        if (currentToken->getType() != L_PAREN) {
            return res->failure(
                    new Error(currentToken->posStart, currentToken->posEnd, currentToken->line, fName, currLine,
                              "InvalidSyntaxError", "Expected '('"));
        }
    } else {
        if (currentToken->getType() != L_PAREN) {
            return res->failure(
                    new Error(currentToken->posStart, currentToken->posEnd, currentToken->line, fName, currLine,
                              "InvalidSyntaxError", "Expected '(' or an identifer"));
        }
    }
    res->regAdvancement();
    advance();
    vector<Token<string> *> argNames;
    if (currentToken->getType() == IDENTIFIER) {
        argNames.push_back((Token<string> *) currentToken);
        res->regAdvancement();
        advance();

        while (currentToken->getType() == COMMA) {
            res->regAdvancement();
            advance();

            if (currentToken->getType() != IDENTIFIER) {
                return res->failure(
                        new Error(currentToken->posStart, currentToken->posEnd, currentToken->line, fName, currLine,
                                  "InvalidSyntaxError", "Expected an identifier"));
            }

            argNames.push_back((Token<string> *) currentToken);
            res->regAdvancement();
            advance();
        }
        if (currentToken->getType() != R_PAREN) {
            return res->failure(
                    new Error(currentToken->posStart, currentToken->posEnd, currentToken->line, fName, currLine,
                              "InvalidSyntaxError", "Expected ',' or ')'"));
        }
    } else {
        if (currentToken->getType() != R_PAREN) {
            return res->failure(
                    new Error(currentToken->posStart, currentToken->posEnd, currentToken->line, fName, currLine,
                              "InvalidSyntaxError", "Expected ',' or ')'"));
        }
    }
    res->regAdvancement();
    advance();

    if (currentToken->getType() == DO) {
        res->regAdvancement();
        advance();
        if(currentToken->getType() == L_CURLY_BRACKET){
            res->regAdvancement();
            advance();
            if(currentToken->getType() == STOP_EXPR){
                res->regAdvancement();
                advance();

                Node* body = res->reg(statements());
                if(res->error) return res;

                if(currentToken->getType() != R_CURLY_BRACKET){
                    return res->failure(
                            new Error(currentToken->posStart, currentToken->posEnd, currentToken->line, fName, currLine,
                                      "InvalidSyntaxError", "Expected '}'"));
                }
                res->regAdvancement();
                advance();

                return res->success(new FuncDefNode(varNameTok, argNames, body, true));
            }
        }

        Node *returnNode = res->reg(expr());
        if (res->error) return res;

        return res->success(new FuncDefNode(varNameTok, argNames, returnNode, false));
    } else{
        return res->failure(
                new Error(currentToken->posStart, currentToken->posEnd, currentToken->line, fName, currLine,
                          "InvalidSyntaxError", "Expected 'do'"));
    }
}

ParseResult *Parser::mapExpr() {
    ParseResult *res = new ParseResult(nullptr, nullptr);
    map<Node *, Node *> map;
    int posStart = currentToken->posStart;

    if (currentToken->getType() != L_CURLY_BRACKET) {
        return res->failure(
                new Error(currentToken->posStart, currentToken->posEnd, currentToken->line, fName, currLine,
                          "InvalidSyntaxError", "Expected '{'"));
    }

    res->regAdvancement();
    advance();

    if (currentToken->getType() == R_CURLY_BRACKET) {
        res->regAdvancement();
        advance();
    } else {
        Node *key = res->reg(expr());
        if (res->error) return res;

        if (currentToken->getType() != COLON) {
            return res->failure(
                    new Error(currentToken->posStart, currentToken->posEnd, currentToken->line, fName, currLine,
                              "InvalidSyntaxError",
                              "Expected a ':'"));
        }
        res->regAdvancement();
        advance();
        Node *value = res->reg(expr());
        if (res->error) {
            return res->failure(
                    new Error(currentToken->posStart, currentToken->posEnd, currentToken->line, fName, currLine,
                              "InvalidSyntaxError",
                              "Expected a '}', identifier, conditional keyword, 'op', or number"));
        }

        map[key] = value;

        while (currentToken->getType() == COMMA) {
            res->regAdvancement();
            advance();
            key = res->reg(expr());
            if (res->error) return res;

            if (currentToken->getType() != COLON) {
                return res->failure(
                        new Error(currentToken->posStart, currentToken->posEnd, currentToken->line, fName, currLine,
                                  "InvalidSyntaxError",
                                  "Expected a ':'"));
            }

            res->regAdvancement();
            advance();

            value = res->reg(expr());
            if (res->error) return res;

            map[key] = value;
        }
        if (currentToken->getType() != R_CURLY_BRACKET) {
            return res->failure(
                    new Error(currentToken->posStart, currentToken->posEnd, currentToken->line, fName, currLine,
                              "InvalidSyntaxError",
                              "Expected ',' or '}'"));
        }
        res->regAdvancement();
        advance();
    }

    return res->success(new MapNode(map, posStart, currentToken->posEnd, currentToken->line));
}

ParseResult *Parser::listExpr() {
    ParseResult *res = new ParseResult(nullptr, nullptr);
    vector<Node *> elements;
    int posStart = currentToken->posStart;

    if (currentToken->getType() != L_BRACKET) {
        return res->failure(
                new Error(currentToken->posStart, currentToken->posEnd, currentToken->line, fName, currLine,
                          "InvalidSyntaxError", "Expected '['"));
    }

    res->regAdvancement();
    advance();

    if (currentToken->getType() == R_BRACKET) {
        res->regAdvancement();
        advance();
    } else {
        elements.push_back(res->reg(expr()));
        if (res->error) {
            return res->failure(
                    new Error(currentToken->posStart, currentToken->posEnd, currentToken->line, fName, currLine,
                              "InvalidSyntaxError",
                              "Expected a ']', identifier, conditional keyword, 'op', or number."));
        }
        while (currentToken->getType() == COMMA) {
            res->regAdvancement();
            advance();
            elements.push_back(res->reg(expr()));
            if (res->error) return res;
        }
        if (currentToken->getType() != R_BRACKET) {
            return res->failure(
                    new Error(currentToken->posStart, currentToken->posEnd, currentToken->line, fName, currLine,
                              "InvalidSyntaxError",
                              "Expected ',' or ']'"));
        }
        res->regAdvancement();
        advance();
    }

    return res->success(new ListNode(elements, posStart, currentToken->posEnd, currentToken->line));
}

ParseResult *Parser::atom() {
    ParseResult *res = new ParseResult(nullptr, nullptr);
    BaseToken *tok = currentToken;

    if (tok->getType() == T_NUM) {
        res->regAdvancement();
        advance();
        return res->success(new NumberNode((Token<double> *) tok));
    } else if (tok->getType() == L_BRACKET) {
        Node *_listExpr = res->reg(listExpr());
        if (res->error) return res;
        return res->success(_listExpr);
    } else if (tok->getType() == L_CURLY_BRACKET) {
        Node *_mapExpr = res->reg(mapExpr());
        if (res->error) return res;
        return res->success(_mapExpr);
    } else if (tok->getType() == T_STRING) {
        res->regAdvancement();
        advance();
        return res->success(new StringNode((Token<string> *) tok));
    } else if (tok->getType() == IF) {
        Node *expr = res->reg(ifExpr());
        if (res->error) return res;
        return res->success(expr);
    } else if (tok->getType() == FOR) {
        Node *forExp = res->reg(forExpr());
        if (res->error) return res;
        return res->success(forExp);
    } else if (tok->getType() == WHILE) {
        Node *whileExp = res->reg(whileExpr());
        if (res->error) return res;
        return res->success(whileExp);
    } else if (tok->getType() == OP) {
        Node *funcDefin = res->reg(funcDef());
        if (res->error) return res;
        return res->success(funcDefin);
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

ParseResult *Parser::call() {
    ParseResult *res = new ParseResult(nullptr, nullptr);
    Node *_atom = res->reg(atom());
    if (res->error) return res;

    if (currentToken->getType() == L_PAREN) {
        res->regAdvancement();
        advance();
        vector<Node *> args;

        if (currentToken->getType() == R_PAREN) {
            res->regAdvancement();
            advance();
        } else {
            args.push_back(res->reg(expr()));
            if (res->error) {
                return res->failure(
                        new Error(currentToken->posStart, currentToken->posEnd, currentToken->line, fName, currLine,
                                  "InvalidSyntaxError",
                                  "Expected a closing parenthesis, identifier, conditional keyword, 'op', or number."));
            }
            while (currentToken->getType() == COMMA) {
                res->regAdvancement();
                advance();
                args.push_back(res->reg(expr()));
                if (res->error) return res;
            }
            if (currentToken->getType() != R_PAREN) {
                return res->failure(
                        new Error(currentToken->posStart, currentToken->posEnd, currentToken->line, fName, currLine,
                                  "InvalidSyntaxError",
                                  "Expected ',' or ')'"));
            }
            res->regAdvancement();
            advance();
        }
        return res->success(new CallNode(_atom, args));
    }
    return res->success(_atom);
}

ParseResult *Parser::power() {
    return binOp({POWER}, &Parser::call, &Parser::factor);
}

ParseResult *Parser::term() {
    return binOp({MULTIPLY, DIVIDE, MOD, GET}, &Parser::factor, &Parser::factor);
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
            binOp({EQUAL_EQUAL, GREATER_THAN, LESS_THAN, LESS_THAN_EQUAL, GREATER_THAN_EQUAL, NOT_EQUAL},
                  &Parser::arithExpr,
                  &Parser::arithExpr));
    if (res->error)
        return res->failure(
                new Error(currentToken->posStart, currentToken->posEnd, currentToken->line, fName, currLine,
                          "InvalidSyntaxError", "Expected a number, identifier, operation, '(', 'NOT' "));
    return res->success(node);

}

ParseResult *Parser::arithExpr() {
    return binOp({PLUS, MINUS, PLUS_EQUAL, MINUS_EQUAL}, &Parser::term, &Parser::term);
}

ParseResult *Parser::statements() {
    ParseResult *res = new ParseResult(nullptr, nullptr);
    vector<Node *> statements;
    int start = currentToken->posStart;

    while (currentToken->getType() == STOP_EXPR) {
        res->regAdvancement();
        advance();
    }

    Node *statement = res->reg(expr());
    if (res->error) return res;
    statements.push_back(statement);

    bool moreStatements = true;

    while (true) {
        int newLineCount = 0;
        while (currentToken->getType() == STOP_EXPR) {
            res->regAdvancement();
            advance();
            newLineCount++;
        }
        if (newLineCount == 0) moreStatements = false;

        if (!moreStatements) break;
        statement = res->tryReg(expr());
        if (!statement) {
            reverse(res->toReverseCount);
            moreStatements = false;
            continue;
        }
        statements.push_back(statement);
    }

    return res->success(
            new ListNode(statements, start, currentToken->posEnd, currentToken->line)
    );
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