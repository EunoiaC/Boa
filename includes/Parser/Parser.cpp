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
    line = 0;
    advance();
}

void Parser::checkNewLines() {
    while (currentToken->getType() == TOK_TYPE::STOP_EXPR) {
        advance();
    }
}

// Check new lines till a certain token is found, if not found, it reverses
bool Parser::checkNewLinesTo(TOK_TYPE type) {
    int rev = 0;
    bool success = true;
    while (currentToken->getType() == TOK_TYPE::STOP_EXPR) {
        advance();
        rev++;
    }
    if (currentToken->getType() != type) {
        reverse(rev);
        success = false;
    }
    return success;
}

BaseToken *Parser::advance() {
    tokIdx++;
    updateCurrentTok();
    return currentToken;
}

BaseToken *Parser::reverse(int amnt) {
    tokIdx -= amnt;
    reversing = true;
    updateCurrentTok();
    return currentToken;
}

void Parser::updateCurrentTok() {
    if (tokIdx >= 0 && tokIdx < tokens.size()) {
        currentToken = tokens[tokIdx];
        if (currentToken->getType() == TOK_TYPE::STOP_EXPR) {
            if (reversing) {
                line--;
                reversing = false;
            } else {
                line++;
            }
        }
        //currLine = currentToken->line < lines.size() ? lines[currentToken->line] : lines[line];
    }
}

ParseResult *Parser::parse() {
    checkNewLines();
    ParseResult *res = statements();
    if (priorityError) return res->failure(priorityError);
    if (!res->error) {
        if (currentToken->getType() != TOK_TYPE::END_OF_FILE && currentToken->getType() != TOK_TYPE::STOP_EXPR) {
            return res->failure(
                    new Error(currentToken->posStart, currentToken->posEnd, currentToken->line, fName, currLine,
                              "InvalidSyntaxError", "Expected an operation"));
        }
    }
    return res;
}

ParseResult *Parser::tryExpr() {
    ParseResult *res = new ParseResult(nullptr, nullptr);

    if (currentToken->getType() != TOK_TYPE::TRY) {
        return res->failure(new Error(currentToken->posStart, currentToken->posEnd, currentToken->line, fName, currLine,
                                      "InvalidSyntaxError", "Expected 'tryto'"));
    }

    delete currentToken;
    res->regAdvancement();
    advance();

    if (currentToken->getType() != TOK_TYPE::DO) {
        return res->failure(new Error(currentToken->posStart, currentToken->posEnd, currentToken->line, fName, currLine,
                                      "InvalidSyntaxError", "Expected 'do'"));
    }

    delete currentToken;
    res->regAdvancement();
    advance();

    checkNewLines();

    Node *tryBody, *catchBody;

    if (currentToken->getType() == TOK_TYPE::L_CURLY_BRACKET) {
        delete currentToken;
        res->regAdvancement();
        advance();
        checkNewLines();

        tryBody = res->reg(statements());
        if (res->error) return res;

        if (currentToken->getType() != TOK_TYPE::R_CURLY_BRACKET) {
            return res->failure(
                    new Error(currentToken->posStart, currentToken->posEnd, currentToken->line, fName, currLine,
                              "InvalidSyntaxError", "Expected '}'"));
        }

        delete currentToken;
        res->regAdvancement();
        advance();
    } else {
        tryBody = res->reg(statement());
        if (res->error) return res;
    }

    if (currentToken->getType() != TOK_TYPE::CATCH) {
        return res->failure(new Error(currentToken->posStart, currentToken->posEnd, currentToken->line, fName, currLine,
                                      "InvalidSyntaxError", "Expected 'catch'"));
    }

    delete currentToken;
    res->regAdvancement();
    advance();

    if (currentToken->getType() != TOK_TYPE::IDENTIFIER) {
        return res->failure(new Error(currentToken->posStart, currentToken->posEnd, currentToken->line, fName, currLine,
                                      "InvalidSyntaxError", "Expected an identifier"));
    }

    Token<string> *toCatch = dynamic_cast<Token<string> *>(currentToken);
    res->regAdvancement();
    advance();

    if (currentToken->getType() != TOK_TYPE::DO) {
        return res->failure(new Error(currentToken->posStart, currentToken->posEnd, currentToken->line, fName, currLine,
                                      "InvalidSyntaxError", "Expected 'do'"));
    }

    delete currentToken;
    res->regAdvancement();
    advance();

    if (currentToken->getType() == TOK_TYPE::L_CURLY_BRACKET) {
        delete currentToken;
        res->regAdvancement();
        advance();
        checkNewLines();

        catchBody = res->reg(statements());
        if (res->error) return res;

        if (currentToken->getType() != TOK_TYPE::R_CURLY_BRACKET) {
            return res->failure(
                    new Error(currentToken->posStart, currentToken->posEnd, currentToken->line, fName, currLine,
                              "InvalidSyntaxError", "Expected '}'"));
        }

        delete currentToken;
        res->regAdvancement();
        advance();
    } else {
        catchBody = res->reg(statement());
        if (res->error) return res;
    }

    return res->success(new TryCatchNode(tryBody, catchBody, toCatch));
}

ParseResult *Parser::ifExpr() {
    ParseResult *res = new ParseResult(nullptr, nullptr);
    Node *elseCase = nullptr;
    vector<tuple<Node *, Node *>> cases;
    if (currentToken->getType() != TOK_TYPE::IF) {
        return res->failure(
                new Error(currentToken->posStart, currentToken->posEnd, currentToken->line, fName, currLine,
                          "InvalidSyntaxError", "Expected 'if'"));
    }
    delete currentToken;
    res->regAdvancement();
    advance();

    Node *condition = res->reg(expr());
    if (res->error) return res;

    if (currentToken->getType() != TOK_TYPE::DO) {
        priorityError = new Error(currentToken->posStart, currentToken->posEnd, currentToken->line, fName, currLine,
                                  "InvalidSyntaxError", "Expected 'do'");
        return res->failure(priorityError);
    }
    delete currentToken;
    res->regAdvancement();
    advance();

    checkNewLines();

    Node *exp;
    if (currentToken->getType() == TOK_TYPE::L_CURLY_BRACKET) {
        delete currentToken;
        res->regAdvancement();
        advance();

        checkNewLines();

        exp = res->reg(statements());
        if (res->error) return res;

        if (currentToken->getType() != TOK_TYPE::R_CURLY_BRACKET) {
            return res->failure(
                    new Error(currentToken->posStart, currentToken->posEnd, currentToken->line, fName, currLine,
                              "InvalidSyntaxError", "Expected '}'"));
        }

        delete currentToken;
        res->regAdvancement();
        advance();

        if (!checkNewLinesTo(TOK_TYPE::ELIF)) {
            checkNewLinesTo(TOK_TYPE::ELSE);
        }
    } else {
        exp = res->reg(statement());
        if (res->error) return res;
    }
    cases.push_back(make_tuple(condition, exp));

    while (currentToken->getType() == TOK_TYPE::ELIF) {
        delete currentToken;
        res->regAdvancement();
        advance();

        condition = res->reg(expr());
        if (res->error) return res;

        if (currentToken->getType() != TOK_TYPE::DO) {
            priorityError = new Error(currentToken->posStart, currentToken->posEnd, currentToken->line, fName, currLine,
                                      "InvalidSyntaxError", "Expected 'do'");
            return res->failure(priorityError);
        }

        delete currentToken;
        res->regAdvancement();
        advance();

        checkNewLines();

        if (currentToken->getType() == TOK_TYPE::L_CURLY_BRACKET) {
            delete currentToken;
            res->regAdvancement();
            advance();

            checkNewLines();

            exp = res->reg(statements());
            if (res->error) return res;

            if (currentToken->getType() != TOK_TYPE::R_CURLY_BRACKET) {
                return res->failure(
                        new Error(currentToken->posStart, currentToken->posEnd, currentToken->line, fName, currLine,
                                  "InvalidSyntaxError", "Expected '}'"));
            }

            delete currentToken;
            res->regAdvancement();
            advance();

            checkNewLinesTo(TOK_TYPE::ELSE);
        } else {
            exp = res->reg(statement());
            if (res->error) return res;
        }
        cases.push_back(make_tuple(condition, exp));
    }

    if (currentToken->getType() == TOK_TYPE::ELSE) {
        delete currentToken;
        res->regAdvancement();
        advance();

        if (currentToken->getType() != TOK_TYPE::DO) {

            priorityError = new Error(currentToken->posStart, currentToken->posEnd, currentToken->line, fName, currLine,
                                      "InvalidSyntaxError", "Expected 'do'");
            return res->failure(
                    priorityError);
        }

        delete currentToken;
        res->regAdvancement();
        advance();

        checkNewLines();

        if (currentToken->getType() == TOK_TYPE::L_CURLY_BRACKET) {
            delete currentToken;
            res->regAdvancement();
            advance();

            checkNewLines();

            elseCase = res->reg(statements());
            if (res->error) return res;

            if (currentToken->getType() != TOK_TYPE::R_CURLY_BRACKET) {
                return res->failure(
                        new Error(currentToken->posStart, currentToken->posEnd, currentToken->line, fName, currLine,
                                  "InvalidSyntaxError", "Expected '}'"));
            }

            delete currentToken;
            res->regAdvancement();
            advance();
        } else {
            elseCase = res->reg(statement());
            if (res->error) return res;
        }
    }
    return res->success(new IfNode(cases, elseCase));
}

ParseResult *Parser::iterExprA() {
    ParseResult *res = new ParseResult(nullptr, nullptr);

    if (currentToken->getType() != TOK_TYPE::ITER) {
        return res->failure(
                new Error(currentToken->posStart, currentToken->posEnd, currentToken->line, fName, currLine,
                          "InvalidSyntaxError", "Expected 'iter'"));
    }

    res->regAdvancement();
    advance();

    if (currentToken->getType() != TOK_TYPE::IDENTIFIER) {
        return res->failure(
                new Error(currentToken->posStart, currentToken->posEnd, currentToken->line, fName, currLine,
                          "InvalidSyntaxError", "Expected an identifier"));
    }

    Token<string> *iterName = dynamic_cast<Token<string> *>(currentToken);
    res->regAdvancement();
    advance();

    if (currentToken->getType() != TOK_TYPE::COLON) {
        return res->failure(
                new Error(currentToken->posStart, currentToken->posEnd, currentToken->line, fName, currLine,
                          "InvalidSyntaxError", "Expected ':'"));
    }
    res->regAdvancement();
    advance();

    return iterExprB(iterName);
}

ParseResult *Parser::iterExprB(Token<string> *iterName) {
    ParseResult *res = new ParseResult(nullptr, nullptr);

    Node *toIter = res->reg(expr());
    if (res->error) return res;

    if (currentToken->getType() != TOK_TYPE::DO) {
        priorityError = new Error(currentToken->posStart, currentToken->posEnd, currentToken->line, fName, currLine,
                                  "InvalidSyntaxError", "Expected 'do'");
        return res->failure(
                priorityError);
    }

    res->regAdvancement();
    advance();

    checkNewLines();

    if (currentToken->getType() == TOK_TYPE::L_CURLY_BRACKET) {
        delete currentToken;
        res->regAdvancement();
        advance();

        while (currentToken->getType() == TOK_TYPE::STOP_EXPR) {
            delete currentToken;
            res->regAdvancement();
            advance();
        }

        Node *body = res->reg(statements());
        if (res->error) return res;

        if (currentToken->getType()  != TOK_TYPE:: R_CURLY_BRACKET) {
            return res->failure(
                    new Error(currentToken->posStart, currentToken->posEnd, currentToken->line, fName, currLine,
                              "InvalidSyntaxError", "Expected '}'"));
        }

        res->regAdvancement();
        advance();

        IterateNode *iterNode = new IterateNode(iterName, toIter, body, true);
        iterNode->line = iterName->line;

        return res->success(iterNode);

    }

    Node *body = res->reg(statement());
    if (res->error) return res;

    return res->success(new IterateNode(iterName, toIter, body, false));
}

ParseResult *Parser::forExpr() {
    ParseResult *res = new ParseResult(nullptr, nullptr);

    if (currentToken->getType()  != TOK_TYPE:: FOR) {
        return res->failure(
                new Error(currentToken->posStart, currentToken->posEnd, currentToken->line, fName, currLine,
                          "InvalidSyntaxError", "Expected 'for'"));
    }
    res->regAdvancement();
    advance();
    if (currentToken->getType()  != TOK_TYPE:: IDENTIFIER) {
        return res->failure(
                new Error(currentToken->posStart, currentToken->posEnd, currentToken->line, fName, currLine,
                          "InvalidSyntaxError", "Expected identifier"));
    }

    Token<string> *identifier = (Token<string> *) currentToken;
    res->regAdvancement();
    advance();

    if (currentToken->getType()  != TOK_TYPE:: EQUAL) {
        if (currentToken->getType() == TOK_TYPE::COLON) {
            res->regAdvancement();
            advance();
            return iterExprB(identifier);
        }
        return res->failure(
                new Error(currentToken->posStart, currentToken->posEnd, currentToken->line, fName, currLine,
                          "InvalidSyntaxError", "Expected '=' or ':'"));
    }

    res->regAdvancement();
    advance();

    Node *startVal = res->reg(expr());
    if (res->error) return res;

    if (currentToken->getType()  != TOK_TYPE:: TO) {
        return res->failure(
                new Error(currentToken->posStart, currentToken->posEnd, currentToken->line, fName, currLine,
                          "InvalidSyntaxError", "Expected 'to'"));
    }

    res->regAdvancement();
    advance();

    Node *endVal = res->reg(expr());
    if (res->error) return res;

    Node *changeVal = nullptr;

    if (currentToken->getType() == TOK_TYPE::CHGBY) {
        res->regAdvancement();
        advance();
        changeVal = res->reg(expr());
        if (res->error) return res;
    }

    if (currentToken->getType()  != TOK_TYPE:: DO) {
        priorityError = new Error(currentToken->posStart, currentToken->posEnd, currentToken->line, fName, currLine,
                                  "InvalidSyntaxError", "Expected 'do'");
        return res->failure(
                priorityError);
    }

    res->regAdvancement();
    advance();

    checkNewLines();

    if (currentToken->getType() == TOK_TYPE::L_CURLY_BRACKET) {
        res->regAdvancement();
        advance();

        while (currentToken->getType() == TOK_TYPE::STOP_EXPR) {
            res->regAdvancement();
            advance();
        }

        Node *body = res->reg(statements());
        if (res->error) return res;

        if (currentToken->getType() != TOK_TYPE::R_CURLY_BRACKET) {
            return res->failure(
                    new Error(currentToken->posStart, currentToken->posEnd, currentToken->line, fName, currLine,
                              "InvalidSyntaxError", "Expected '}'"));
        }

        res->regAdvancement();
        advance();

        return res->success(new ForNode(identifier, startVal, endVal, changeVal, body, true));
    }

    Node *body = res->reg(statement());
    if (res->error) return res;

    return res->success(new ForNode(identifier, startVal, endVal, changeVal, body, false));
}

ParseResult *Parser::whileExpr() {
    ParseResult *res = new ParseResult(nullptr, nullptr);
    if (currentToken->getType()  != TOK_TYPE:: WHILE) {
        return res->failure(
                new Error(currentToken->posStart, currentToken->posEnd, currentToken->line, fName, currLine,
                          "InvalidSyntaxError", "Expected 'while'"));
    }

    res->regAdvancement();
    advance();

    Node *condition = res->reg(expr());
    if (res->error) return res;

    if (currentToken->getType()  != TOK_TYPE:: DO) {
        priorityError = new Error(currentToken->posStart, currentToken->posEnd, currentToken->line, fName, currLine,
                                  "InvalidSyntaxError", "Expected 'do'");
        return res->failure(
                priorityError);
    }

    res->regAdvancement();
    advance();

    checkNewLines();

    if (currentToken->getType() == TOK_TYPE::L_CURLY_BRACKET) {
        res->regAdvancement();
        advance();

        checkNewLines();

        Node *body = res->reg(statements());
        if (res->error) return res;

        if (currentToken->getType()  != TOK_TYPE:: R_CURLY_BRACKET) {
            return res->failure(
                    new Error(currentToken->posStart, currentToken->posEnd, currentToken->line, fName, currLine,
                              "InvalidSyntaxError", "Expected '}'"));
        }

        res->regAdvancement();
        advance();

        return res->success(new WhileNode(condition, body, true));
    }

    Node *body = res->reg(statement());
    if (res->error) return res;

    return res->success(new WhileNode(condition, body, false));
}

ParseResult *Parser::funcDef() {
    ParseResult *res = new ParseResult(nullptr, nullptr);
    if (currentToken->getType()  != TOK_TYPE:: OP) {
        return res->failure(
                new Error(currentToken->posStart, currentToken->posEnd, currentToken->line, fName, currLine,
                          "InvalidSyntaxError", "Expected 'op'"));
    }

    res->regAdvancement();
    advance();
    Token<string> *varNameTok = new Token<string>(TOK_TYPE::T_STRING, "anonymous", currentToken->posStart, currentToken->posEnd,
                                                  currentToken->line);
    if (currentToken->getType() == TOK_TYPE::IDENTIFIER) {
        varNameTok = (Token<string> *) currentToken;
        res->regAdvancement();
        advance();
        if (currentToken->getType()  != TOK_TYPE:: L_PAREN) {
            return res->failure(
                    new Error(currentToken->posStart, currentToken->posEnd, currentToken->line, fName, currLine,
                              "InvalidSyntaxError", "Expected '('"));
        }
    } else {
        if (currentToken->getType()  != TOK_TYPE:: L_PAREN) {
            return res->failure(
                    new Error(currentToken->posStart, currentToken->posEnd, currentToken->line, fName, currLine,
                              "InvalidSyntaxError", "Expected '(' or an identifer"));
        }
    }
    res->regAdvancement();
    advance();
    vector<Token<string> *> argNames;
    bool defaultArgs = false;
    map<string, Node *> defaultArgValues;

    if (currentToken->getType() == TOK_TYPE::IDENTIFIER) {
        Token<string> *argName = (Token<string> *) currentToken;
        argNames.push_back(argName);

        res->regAdvancement();
        advance();

        if (currentToken->getType() == TOK_TYPE::EQUAL) {
            defaultArgs = true;

            res->regAdvancement();
            advance();

            Node *expr_ = res->reg(expr());
            if (res->error) return res;
            defaultArgValues[argName->getValueObject()->getValue()] = expr_;
        }

        while (currentToken->getType() == TOK_TYPE::COMMA) {
            res->regAdvancement();
            advance();

            if (currentToken->getType()  != TOK_TYPE:: IDENTIFIER) {
                return res->failure(
                        new Error(currentToken->posStart, currentToken->posEnd, currentToken->line, fName, currLine,
                                  "InvalidSyntaxError", "Expected an identifier"));
            }

            argName = (Token<string> *) currentToken;
            argNames.push_back(argName);

            res->regAdvancement();
            advance();

            if (currentToken->getType() == TOK_TYPE::EQUAL) {
                defaultArgs = true;

                res->regAdvancement();
                advance();

                Node *expr_ = res->reg(expr());
                if (res->error) return res;
                defaultArgValues[argName->getValueObject()->getValue()] = expr_;
            } else if (defaultArgs) {
                priorityError = new Error(argName->posStart, argName->posEnd, argName->line, fName, currLine,
                                          "InvalidSyntaxError", "Normal arguments must be before default arguments");
                return res->failure(
                        priorityError);
            }
        }
        if (currentToken->getType()  != TOK_TYPE:: R_PAREN) {
            return res->failure(
                    new Error(currentToken->posStart, currentToken->posEnd, currentToken->line, fName, currLine,
                              "InvalidSyntaxError", "Expected ',' or ')'"));
        }
    } else {
        if (currentToken->getType()  != TOK_TYPE:: R_PAREN) {
            return res->failure(
                    new Error(currentToken->posStart, currentToken->posEnd, currentToken->line, fName, currLine,
                              "InvalidSyntaxError", "Expected ',' or ')'"));
        }
    }
    res->regAdvancement();
    advance();

    if (currentToken->getType() == TOK_TYPE::INFIX) {
        infixFuncs.push_back(varNameTok->getValueObject()->getValue());
        res->regAdvancement();
        advance();
    }

    vector<string> uses;

    if (currentToken->getType() == TOK_TYPE::USES) {
        delete currentToken;
        res->regAdvancement();
        advance();

        if (currentToken->getType()  != TOK_TYPE:: L_BRACKET) {
            return res->failure(
                    new Error(currentToken->posStart, currentToken->posEnd, currentToken->line, fName, currLine,
                              "InvalidSyntaxError", "Expected '['"));
        }
        delete currentToken;
        res->regAdvancement();
        advance();

        if (currentToken->getType()  != TOK_TYPE:: IDENTIFIER) {
            return res->failure(
                    new Error(currentToken->posStart, currentToken->posEnd, currentToken->line, fName, currLine,
                              "InvalidSyntaxError", "Expected an identifier"));
        }
        uses.push_back(((Token<string> *) currentToken)->getValueObject()->getValue());
        res->regAdvancement();
        advance();

        while (currentToken->getType() == TOK_TYPE::COMMA) {
            delete currentToken;
            res->regAdvancement();
            advance();

            if (currentToken->getType()  != TOK_TYPE:: IDENTIFIER) {
                return res->failure(
                        new Error(currentToken->posStart, currentToken->posEnd, currentToken->line, fName, currLine,
                                  "InvalidSyntaxError", "Expected an identifier"));
            }
            uses.push_back(((Token<string> *) currentToken)->getValueObject()->getValue());
            res->regAdvancement();
            advance();
        }

        if (currentToken->getType()  != TOK_TYPE::  R_BRACKET) {
            return res->failure(
                    new Error(currentToken->posStart, currentToken->posEnd, currentToken->line, fName, currLine,
                              "InvalidSyntaxError", "Expected ']'"));
        }
        delete currentToken;
        res->regAdvancement();
        advance();
    }

    if (currentToken->getType() == TOK_TYPE::DO) {
        delete currentToken;
        res->regAdvancement();
        advance();
        checkNewLines();
        if (currentToken->getType() == TOK_TYPE::L_CURLY_BRACKET) {
            res->regAdvancement();
            advance();

            checkNewLines();

            Node *body = res->reg(statements());
            if (res->error) return res;

            if (currentToken->getType()  != TOK_TYPE::  R_CURLY_BRACKET) {
                return res->failure(
                        new Error(currentToken->posStart, currentToken->posEnd, currentToken->line, fName, currLine,
                                  "InvalidSyntaxError", "Expected '}'"));
            }
            res->regAdvancement();
            advance();
            // Multiple statements
            return res->success(new FuncDefNode(varNameTok, argNames, defaultArgValues, uses, body, false));

        }

        Node *returnNode = res->reg(statement());
        if (res->error) return res;
        // Single line function
        return res->success(new FuncDefNode(varNameTok, argNames, defaultArgValues, uses, returnNode, true));
    } else {
        priorityError = new Error(currentToken->posStart, currentToken->posEnd, currentToken->line, fName, currLine,
                                  "InvalidSyntaxError", "Expected 'do'");
        return res->failure(
                priorityError);
    }
}

ParseResult *Parser::mapExpr() {
    ParseResult *res = new ParseResult(nullptr, nullptr);
    map<Node *, Node *> map;
    int posStart = currentToken->posStart;

    if (currentToken->getType()  != TOK_TYPE::  L_CURLY_BRACKET) {
        return res->failure(
                new Error(currentToken->posStart, currentToken->posEnd, currentToken->line, fName, currLine,
                          "InvalidSyntaxError", "Expected '{'"));
    }

    res->regAdvancement();
    advance();

    checkNewLines();

    if (currentToken->getType() == TOK_TYPE::R_CURLY_BRACKET) {
        res->regAdvancement();
        advance();
    } else {
        Node *key = res->reg(expr());
        if (res->error) return res;

        if (currentToken->getType()  != TOK_TYPE::  COLON) {
            return res->failure(
                    new Error(currentToken->posStart, currentToken->posEnd, currentToken->line, fName, currLine,
                              "InvalidSyntaxError",
                              "Expected a ':'"));
        }
        res->regAdvancement();
        advance();
        Node *value = res->reg(expr());
        if (res->error) {
            priorityError = new Error(currentToken->posStart, currentToken->posEnd, currentToken->line, fName, currLine,
                                      "InvalidSyntaxError",
                                      "Expected a '}', identifier, conditional keyword, 'op', or value");
            return res->failure(priorityError);
        }

        map[key] = value;

        while (currentToken->getType() == TOK_TYPE::COMMA) {
            res->regAdvancement();
            advance();

            checkNewLines();

            key = res->reg(expr());
            if (res->error) { ;
                priorityError = new Error(currentToken->posStart, currentToken->posEnd, currentToken->line, fName,
                                          currLine,
                                          "InvalidSyntaxError",
                                          "Expected an identifier, conditional keyword, 'op', or value");
                return res->failure(priorityError);
            }

            if (currentToken->getType()  != TOK_TYPE::  COLON) {
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
        bool success = checkNewLinesTo(TOK_TYPE::R_CURLY_BRACKET);
        if (!success) {
            priorityError = new Error(currentToken->posStart, currentToken->posEnd, currentToken->line, fName, currLine,
                                      "InvalidSyntaxError",
                                      "Expected ',' or '}'");
            return res->failure(priorityError);
        }
        res->regAdvancement();
        advance();
    }

    return res->success(new MapNode(map, posStart, currentToken->posEnd, currentToken->line));
}

ParseResult *Parser::classDef() {
    ParseResult *res = new ParseResult(nullptr, nullptr);
    if (currentToken->getType()  != TOK_TYPE::  CLASS) {
        res->failure(
                new Error(currentToken->posStart, currentToken->posEnd, currentToken->line, fName, currLine,
                          "InvalidSyntaxError", "Expected 'class'"));
    }
    delete currentToken;

    res->regAdvancement();
    advance();

    if (currentToken->getType()  != TOK_TYPE::  IDENTIFIER) {
        return res->failure(
                new Error(currentToken->posStart, currentToken->posEnd, currentToken->line, fName, currLine,
                          "InvalidSyntaxError", "Expected an identifier"));
    }
    Token<string> *className = dynamic_cast<Token<string> *>(currentToken);
    res->regAdvancement();
    advance();

    Token<string> *varNameTok = nullptr;
    if (currentToken->getType() == TOK_TYPE::IDENTIFIER) {
        varNameTok = (Token<string> *) currentToken;
        res->regAdvancement();
        advance();
        if (currentToken->getType()  != TOK_TYPE::  L_PAREN) {
            return res->failure(
                    new Error(currentToken->posStart, currentToken->posEnd, currentToken->line, fName, currLine,
                              "InvalidSyntaxError", "Expected '('"));
        }
    } else {
        if (currentToken->getType()  != TOK_TYPE::  L_PAREN) {
            return res->failure(
                    new Error(currentToken->posStart, currentToken->posEnd, currentToken->line, fName, currLine,
                              "InvalidSyntaxError", "Expected '(' or an identifer"));
        }
    }
    res->regAdvancement();
    advance();

    vector<Token<string> *> argNames;
    bool defaultArgs = false;
    map<string, Node *> defaultArgValues;

    if (currentToken->getType() == TOK_TYPE::IDENTIFIER) {
        Token<string> *argName = (Token<string> *) currentToken;
        argNames.push_back(argName);

        res->regAdvancement();
        advance();

        if (currentToken->getType() == TOK_TYPE::EQUAL) {
            defaultArgs = true;

            res->regAdvancement();
            advance();

            Node *expr_ = res->reg(expr());
            if (res->error) return res;
            defaultArgValues[argName->getValueObject()->getValue()] = expr_;
        }

        while (currentToken->getType() == TOK_TYPE::COMMA) {
            res->regAdvancement();
            advance();

            if (currentToken->getType()  != TOK_TYPE::  IDENTIFIER) {
                return res->failure(
                        new Error(currentToken->posStart, currentToken->posEnd, currentToken->line, fName, currLine,
                                  "InvalidSyntaxError", "Expected an identifier"));
            }

            argName = (Token<string> *) currentToken;
            argNames.push_back(argName);

            res->regAdvancement();
            advance();

            if (currentToken->getType() == TOK_TYPE::EQUAL) {
                defaultArgs = true;

                res->regAdvancement();
                advance();

                Node *expr_ = res->reg(expr());
                if (res->error) return res;
                defaultArgValues[argName->getValueObject()->getValue()] = expr_;
            } else if (defaultArgs) {
                priorityError = new Error(argName->posStart, argName->posEnd, argName->line, fName, currLine,
                                          "InvalidSyntaxError", "Normal arguments must be before default arguments");
                return res->failure(
                        priorityError);
            }
        }
        if (currentToken->getType()  != TOK_TYPE::  R_PAREN) {
            return res->failure(
                    new Error(currentToken->posStart, currentToken->posEnd, currentToken->line, fName, currLine,
                              "InvalidSyntaxError", "Expected ',' or ')'"));
        }
    } else {
        if (currentToken->getType()  != TOK_TYPE::  R_PAREN) {
            return res->failure(
                    new Error(currentToken->posStart, currentToken->posEnd, currentToken->line, fName, currLine,
                              "InvalidSyntaxError", "Expected ',' or ')'"));
        }
    }

    delete currentToken;
    res->regAdvancement();
    advance();

    Node *parentClass = nullptr;
    if (currentToken->getType() == TOK_TYPE::COLON) {
        delete currentToken;
        res->regAdvancement();
        advance();

        int posStart = currentToken->posStart;

        parentClass = res->reg(call());
        if (res->error) return res;

        int posEnd = currentToken->posEnd;

        parentClass->posStart = posStart;
        parentClass->posEnd = tokens[tokIdx - 1]->posEnd;
        parentClass->line = currentToken->line;

        if (parentClass->type != N_CALL) {
            return res->failure(
                    new Error(parentClass->posStart, parentClass->posEnd, parentClass->line, fName, currLine,
                              "InvalidSyntaxError", "Expected a class name with constructor args"));
        }
    }

    if (currentToken->getType()  != TOK_TYPE::  DO) {
        return res->failure(
                new Error(currentToken->posStart, currentToken->posEnd, currentToken->line, fName, currLine,
                          "InvalidSyntaxError", "Expected 'do'"));
    }

    delete currentToken;
    res->regAdvancement();
    advance();

    if (currentToken->getType()  != TOK_TYPE::  L_CURLY_BRACKET) {
        return res->failure(
                new Error(currentToken->posStart, currentToken->posEnd, currentToken->line, fName, currLine,
                          "InvalidSyntaxError", "Expected '{'"));
    }

    delete currentToken;
    res->regAdvancement();
    advance();

    checkNewLines();

    vector<Node *> members;
    while (currentToken->getType()  != TOK_TYPE::  R_CURLY_BRACKET) {
        members.push_back(res->reg(statement()));
        if (res->error) return res;
        checkNewLines();
    }

    delete currentToken;
    res->regAdvancement();
    advance();

    ClassDefNode *classDef = new ClassDefNode(className, argNames, defaultArgValues, members, parentClass);

    return res->success(classDef);
}

ParseResult *Parser::listExpr() {
    ParseResult *res = new ParseResult(nullptr, nullptr);
    vector<Node *> elements;
    int posStart = currentToken->posStart;

    if (currentToken->getType()  != TOK_TYPE::  L_BRACKET) {
        return res->failure(
                new Error(currentToken->posStart, currentToken->posEnd, currentToken->line, fName, currLine,
                          "InvalidSyntaxError", "Expected '['"));
    }

    res->regAdvancement();
    advance();

    checkNewLines();

    if (currentToken->getType() == TOK_TYPE::R_BRACKET) {
        res->regAdvancement();
        advance();
    } else {
        elements.push_back(res->reg(expr()));
        if (res->error) {
            priorityError = new Error(currentToken->posStart, currentToken->posEnd, currentToken->line, fName, currLine,
                                      "InvalidSyntaxError",
                                      "Expected a ',' or ']'");
            return res->failure(priorityError);
        }
        while (currentToken->getType() == TOK_TYPE::COMMA) {
            res->regAdvancement();
            advance();

            checkNewLines();

            elements.push_back(res->reg(expr()));
            if (res->error) return res;
        }
        bool success = checkNewLinesTo(TOK_TYPE::R_BRACKET);
        if (!success) {
            priorityError = new Error(currentToken->posStart, currentToken->posEnd, currentToken->line, fName,
                                      lines[currentToken->line],
                                      "InvalidSyntaxError",
                                      "Expected ',' or ']'");
            return res->failure(priorityError);
        }
        res->regAdvancement();
        advance();
    }

    return res->success(new ListNode(elements, posStart, currentToken->posEnd, currentToken->line));
}

ParseResult *Parser::atom() {
    ParseResult *res = new ParseResult(nullptr, nullptr);
    BaseToken *tok = currentToken;

    if (tok->getType() == TOK_TYPE::T_NUM) {
        res->regAdvancement();
        advance();
        return res->success(new NumberNode((Token<double> *) tok));
    } else if (tok->getType() == TOK_TYPE::EITHER) {
        Node *either = res->reg(eitherExpr());
        if (res->error) return res;
        return res->success(either);
    } else if (tok->getType() == TOK_TYPE::TRY) {
        Node *_try = res->reg(tryExpr());
        if (res->error) return res;
        return res->success(_try);
    } else if (tok->getType() == TOK_TYPE::CLASS) {
        Node *_classDef = res->reg(classDef());
        if (res->error) return res;
        return res->success(_classDef);
    } else if (tok->getType() == TOK_TYPE::L_BRACKET) {
        Node *_listExpr = res->reg(listExpr());
        if (res->error) return res;
        return res->success(_listExpr);
    } else if (tok->getType() == TOK_TYPE::L_CURLY_BRACKET) {
        Node *_mapExpr = res->reg(mapExpr());
        if (res->error) return res;
        return res->success(_mapExpr);
    } else if (tok->getType() == TOK_TYPE::T_STRING) {
        res->regAdvancement();
        advance();
        return res->success(new StringNode((Token<string> *) tok));
    } else if (tok->getType() == TOK_TYPE::IF) {
        Node *expr = res->reg(ifExpr());
        if (res->error) return res;
        return res->success(expr);
    } else if (tok->getType() == TOK_TYPE::FOR) {
        Node *forExp = res->reg(forExpr());
        if (res->error) return res;
        return res->success(forExp);
    } else if (tok->getType() == TOK_TYPE::ITER) {
        Node *iterExp = res->reg(iterExprA());
        if (res->error) return res;
        return res->success(iterExp);
    } else if (tok->getType() == TOK_TYPE::WHILE) {
        Node *whileExp = res->reg(whileExpr());
        if (res->error) return res;
        return res->success(whileExp);
    } else if (tok->getType() == TOK_TYPE::OP) {
        Node *funcDefin = res->reg(funcDef());
        if (res->error) return res;
        return res->success(funcDefin);
    } else if (tok->getType() == TOK_TYPE::IDENTIFIER) {
        res->regAdvancement();
        advance();
        TOK_TYPE type = currentToken->getType();
        //If the token is equal, we assign a new variable to the node
        vector<BaseToken *> identifiers;
        while (currentToken->getType() == TOK_TYPE::DOT) {
            delete currentToken;
            res->regAdvancement();
            advance();
            if (currentToken->getType()  != TOK_TYPE::  IDENTIFIER) {
                priorityError = new Error(currentToken->posStart, currentToken->posEnd, currentToken->line, fName,
                                          lines[currentToken->line],
                                          "InvalidSyntaxError",
                                          "Expected an identifier");
                return res->failure(priorityError);
            }
            identifiers.push_back(currentToken);
            res->regAdvancement();
            advance();
        }
        if (currentToken->getType() == TOK_TYPE::EQUAL) {
            delete currentToken;
            res->regAdvancement();
            advance();
            Node *exp = res->reg(expr());
            if (res->error) return res;
            return res->success(new VarAssignNode((Token<string> *) tok, exp, identifiers, REASSIGN_VAR));
        }
        if (currentToken->getType() == TOK_TYPE::TO) {
            delete currentToken;
            res->regAdvancement();
            advance();
            Node *exp = res->reg(expr());
            if (res->error) return res;
            return res->success(new VarAssignNode((Token<string> *) tok, exp, identifiers, NEW_VALUE));
        }
        return res->success(new VarAccessNode((Token<string> *) tok, identifiers, nullptr));
    } else if (tok->getType() == TOK_TYPE::L_PAREN) {
        res->regAdvancement();
        advance();
        Node *exp = res->reg(expr());
        if (res->error) return res;
        if (currentToken->getType() == TOK_TYPE::R_PAREN) {
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
    if (tok->getType() == TOK_TYPE::PLUS || tok->getType() == TOK_TYPE::MINUS) {
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

    if (currentToken->getType() == TOK_TYPE::IDENTIFIER) {
        Token<string> *infixFunc = ((Token<string> *) currentToken);

        if (find(infixFuncs.begin(), infixFuncs.end(), infixFunc->getValueObject()->getValue()) != infixFuncs.end()) {
            res->regAdvancement();
            advance();

            Node *ato = res->reg(atom());
            if (res->error) return res;

            _atom = new VarAccessNode(nullptr, {infixFunc}, _atom);
            return res->success(new CallNode(_atom, {ato}));
        } else {
            priorityError = new Error(infixFunc->posStart, infixFunc->posEnd, infixFunc->line, fName,
                                      currLine, "InvalidSyntaxError",
                                      "Expected an infix function, operator, comparison, or '('");
            return res->failure(priorityError);
        }
    }

    vector<Node *> indices;

    while (currentToken->getType() == TOK_TYPE::L_BRACKET) {
        res->regAdvancement();
        advance();

        Node *index = res->reg(expr());
        if (res->error) return res;

        if (currentToken->getType()  != TOK_TYPE::  R_BRACKET) {
            priorityError = new Error(currentToken->posStart, currentToken->posEnd, currentToken->line, fName,
                                      lines[currentToken->line],
                                      "InvalidSyntaxError",
                                      "Expected a closing bracket");
            return res->failure(priorityError);
        }
        res->regAdvancement();
        advance();
        indices.push_back(index);
    }

    if (indices.size() > 0) {
        IndexNode *index = new IndexNode(_atom, indices, GET_VALUE);
        index->line = currentToken->line;

        if (currentToken->getType() == TOK_TYPE::EQUAL) {
            delete currentToken;
            res->regAdvancement();
            advance();
            Node *exp = res->reg(expr());
            if (res->error) return res;

            index->type = SET_VALUE;
            index->newVal = exp;
        }
        _atom = index;
    }

    if (currentToken->getType() == TOK_TYPE::DOT) {
        vector<BaseToken *> identifiers;
        res->regAdvancement();
        advance();
        if (currentToken->getType()  != TOK_TYPE::  IDENTIFIER) {
            return res->failure(
                    new Error(currentToken->posStart, currentToken->posEnd, currentToken->line, fName, currLine,
                              "InvalidSyntaxError", "Expected an identifier"));
        }
        identifiers.push_back(currentToken);
        res->regAdvancement();
        advance();
        while (currentToken->getType() == TOK_TYPE::DOT) {
            res->regAdvancement();
            advance();
            if (currentToken->getType()  != TOK_TYPE:: IDENTIFIER) {
                return res->failure(
                        new Error(currentToken->posStart, currentToken->posEnd, currentToken->line, fName, currLine,
                                  "InvalidSyntaxError", "Expected an identifier"));
            }
            identifiers.push_back(currentToken);
            res->regAdvancement();
            advance();
        }
        _atom = new VarAccessNode(nullptr, identifiers, _atom);
    }


    if (currentToken->getType() == TOK_TYPE::L_PAREN) {
        res->regAdvancement();
        advance();
        vector<Node *> args;

        checkNewLines();

        if (currentToken->getType() == TOK_TYPE::R_PAREN) {
            delete currentToken;
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
            checkNewLines();
            while (currentToken->getType() == TOK_TYPE::COMMA) {
                delete currentToken;
                res->regAdvancement();
                advance();
                checkNewLines();
                args.push_back(res->reg(expr()));
                if (res->error) return res;
            }
            bool success = checkNewLinesTo(TOK_TYPE::R_PAREN);
            if (!success) {
                if (!(currentToken->getType() == TOK_TYPE::STOP_EXPR)) reverse(1);
                priorityError = new Error(currentToken->posStart, currentToken->posEnd, currentToken->line, fName,
                                          lines[currentToken->line],
                                          "InvalidSyntaxError",
                                          "Expected a  ',' or ')'");
                return res->failure(priorityError);
            }
            delete currentToken;
            res->regAdvancement();
            advance();
        }
        CallNode *call = new CallNode(_atom, args);

        call->line = call->nodeToCall->line;
        return res->success(call);
    }
    return res->success(_atom);
}

ParseResult *Parser::power() {
    return binOp({TOK_TYPE::POWER, TOK_TYPE::DOT, TOK_TYPE::GET}, &Parser::call, &Parser::factor);
}

ParseResult *Parser::term() {
    return binOp({TOK_TYPE::MULTIPLY, TOK_TYPE::DIVIDE, TOK_TYPE::MOD}, &Parser::factor, &Parser::factor);
}

ParseResult *Parser::eitherExpr() {
    ParseResult *res = new ParseResult(nullptr, nullptr);
    if (currentToken->getType()  != TOK_TYPE::  EITHER) {
        return res->failure(
                new Error(currentToken->posStart, currentToken->posEnd, currentToken->line, fName, currLine,
                          "InvalidSyntaxError",
                          "Expected 'either'"));
    }
    delete currentToken;
    res->regAdvancement();
    advance();

    Node *curr = res->reg(arithExpr());
    if (res->error) return res;

    vector<Node *> cases;
    cases.push_back(curr);

    if (currentToken->getType()  != TOK_TYPE::  OR) {
        return res->failure(
                new Error(currentToken->posStart, currentToken->posEnd, currentToken->line, fName, currLine,
                          "InvalidSyntaxError",
                          "Expected 'or'"));
    }

    while (currentToken->getType() == TOK_TYPE::OR) {
        delete currentToken;
        res->regAdvancement();
        advance();

        curr = res->reg(arithExpr());
        if (res->error) return res;
        cases.push_back(curr);
    }

    EitherNode *either = new EitherNode(cases);
    return res->success(either);
}

ParseResult *Parser::compExpr() {
    ParseResult *res = new ParseResult(nullptr, nullptr);
    Node *node;

    if (currentToken->getType() == TOK_TYPE::NOT) {
        auto opTok = currentToken;
        res->regAdvancement();
        advance();
        node = res->reg(compExpr());
        if (res->error) return res;
        return res->success(new UnaryOperationNode((Token<string> *) opTok, node));
    }

    node = res->reg(
            binOp({TOK_TYPE::EQUAL_EQUAL, TOK_TYPE::GREATER_THAN, TOK_TYPE::LESS_THAN, TOK_TYPE::LESS_THAN_EQUAL, TOK_TYPE::GREATER_THAN_EQUAL, TOK_TYPE::NOT_EQUAL, TOK_TYPE::CONTAINS},
                  &Parser::arithExpr,
                  &Parser::arithExpr));
    if (res->error)
        return res->failure(
                new Error(currentToken->posStart, currentToken->posEnd, currentToken->line, fName, currLine,
                          "InvalidSyntaxError", "Expected a number, identifier, operation, '(', 'NOT' "));
    return res->success(node);

}

ParseResult *Parser::arithExpr() {
    return binOp({TOK_TYPE::PLUS, TOK_TYPE::MINUS, TOK_TYPE::PLUS_EQUAL, TOK_TYPE::MINUS_EQUAL}, &Parser::term, &Parser::term);
}

ParseResult *Parser::statement() {
    ParseResult *res = new ParseResult(nullptr, nullptr);
    int posStart = currentToken->posStart;

    Node *_expr = nullptr;

    if (currentToken->type == TOK_TYPE::IMPORT) {
        delete currentToken;
        res->regAdvancement();
        advance();

        Token<string> *tok = nullptr;

        if (currentToken->getType() == TOK_TYPE::IDENTIFIER) {
            tok = dynamic_cast<Token<string> *>(currentToken);
            res->regAdvancement();
            advance();

            if (currentToken->getType()  != TOK_TYPE::  FROM) {
                return res->failure(
                        new Error(currentToken->posStart, currentToken->posEnd, currentToken->line, fName, currLine,
                                  "InvalidSyntaxError",
                                  "Expected 'from'"));
            }

            delete currentToken;
            res->regAdvancement();
            advance();
        }

        _expr = res->reg(expr());
        if (res->error) return res;

        return res->success(new ImportNode(_expr, tok, posStart, currentToken->posEnd, currentToken->line));
    }

    if (currentToken->getType() == TOK_TYPE::RETURN) {
        delete currentToken;
        res->regAdvancement();
        advance();

        _expr = res->tryReg(expr());
        if (!_expr) {
            reverse(res->toReverseCount);
        }

        return res->success(new ReturnNode(_expr, posStart, currentToken->posEnd, currentToken->line));
    }

    if (currentToken->getType() == TOK_TYPE::CONTINUE) {
        delete currentToken;
        res->regAdvancement();
        advance();

        return res->success(new ContinueNode(posStart, currentToken->posEnd, currentToken->line));
    }

    if (currentToken->getType() == TOK_TYPE::BREAK) {
        delete currentToken;
        res->regAdvancement();
        advance();

        return res->success(new BreakNode(posStart, currentToken->posEnd, currentToken->line));
    }

    _expr = res->reg(expr());
    if (res->error)
        return res->failure(
                new Error(currentToken->posStart, currentToken->posEnd, currentToken->line, fName, currLine,
                          "InvalidSyntaxError",
                          "Expected return, continue, break, a value type, identifier, operation, '(', or 'NOT' "));

    return res->success(_expr);
}

ParseResult *Parser::statements() {
    ParseResult *res = new ParseResult(nullptr, nullptr);
    vector<Node *> statements;
    int start = currentToken->posStart;

    Node *statement_ = res->reg(statement());
    if (res->error) return res;
    statements.push_back(statement_);

    bool moreStatements = true;

    while (true) {
        int newLineCount = 0;
        while (currentToken->getType() == TOK_TYPE::STOP_EXPR) {
            delete currentToken;
            res->regAdvancement();
            advance();
            newLineCount++;
        }
        if (newLineCount == 0) moreStatements = false;

        if (!moreStatements) break;

        statement_ = res->tryReg(statement());
        if (!statement_) {
            reverse(res->toReverseCount);
            moreStatements = false;
            continue;
        }
        statements.push_back(statement_);
    }

    return res->success(
            new ListNode(statements, start, currentToken->posEnd, currentToken->line)
    );
}

ParseResult *Parser::expr() {
    ParseResult *res = new ParseResult(nullptr, nullptr);

    // Prioritize awaits
    if (currentToken->getType() == TOK_TYPE::AWAIT) {
        int posStart = currentToken->posStart;
        delete currentToken;
        res->regAdvancement();
        advance();

        Node *_expr = res->reg(call());
        if (res->error) {
            priorityError = new Error(currentToken->posStart, currentToken->posEnd, currentToken->line, fName, currLine,
                                      "InvalidSyntaxError",
                                      "Expected a function call");
            return res->failure(priorityError);
        }

        return res->success(new AwaitNode(_expr, posStart, currentToken->posEnd, currentToken->line));
    }

    Node *node = res->reg(binOp({TOK_TYPE::AND, TOK_TYPE::OR}, &Parser::compExpr, &Parser::compExpr));
    if (res->error)
        return res->failure(
                new Error(currentToken->posStart, currentToken->posEnd, currentToken->line, fName, currLine,
                          "InvalidSyntaxError", "Expected an operation, identifier, number, or '('"));
    return res->success(node);
}

ParseResult *Parser::binOp(vector<TOK_TYPE> ops, ParseResult *(Parser::*funcA)(), ParseResult *(Parser::*funcB)()) {
    ParseResult *res = new ParseResult(nullptr, nullptr);

    Node *left = res->reg((this->*funcA)());
    if (res->error) return res;

    while (find(ops.begin(), ops.end(), currentToken->getType()) != ops.end()) {
        BaseToken *opTok = currentToken;
        // Don't delete the operator token, it's needed for the next iteration
        res->regAdvancement();
        advance();

        Node *right = res->reg((this->*funcB)());
        if (res->error) return res;

        left = new BinaryOperationNode(left, (Token<string> *) opTok, right);
        left->line = opTok->line;
    }
    return res->success(left);
}