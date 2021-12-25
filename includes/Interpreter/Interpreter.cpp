//
// Created by Aadi Yadav on 11/20/21.
//

#include <iostream>
#include "Interpreter.h"

Interpreter::Interpreter(string name, vector<string> l) {
    fName = name;
    lines = l;
    funcMap[N_UNOP] = &Interpreter::visitUnaryOpNode;
    funcMap[N_BINOP] = &Interpreter::visitBinOpNode;
    funcMap[N_NUMBER] = &Interpreter::visitNumberNode;
    funcMap[N_STRING] = &Interpreter::visitStringNode;
    funcMap[N_LIST] = &Interpreter::visitListNode;
    funcMap[N_MAP] = &Interpreter::visitMapNode;
    funcMap[N_VAR_ACCESS] = &Interpreter::visitVarAccessNode;
    funcMap[N_VAR_ASSIGN] = &Interpreter::visitVarAssignNode;
    funcMap[N_IF] = &Interpreter::visitIfNode;
    funcMap[N_FOR] = &Interpreter::visitForNode;
    funcMap[N_WHILE] = &Interpreter::visitWhileNode;
    funcMap[N_CALL] = &Interpreter::visitCallNode;
    funcMap[N_FUNC_DEF] = &Interpreter::visitFuncDefNode;
}

RuntimeResult *Interpreter::visit(Node *n, Context *c) {
    string methodName = n->type;
    return (this->*funcMap[methodName])(n, c);
}

RuntimeResult *Interpreter::visitForNode(Node *n, Context *c) {
    RuntimeResult *res = new RuntimeResult();
    ForNode *forNode = (ForNode *) n;
    vector<BaseValue *> elements;

    Number<double> *startVal = (Number<double> *) res->reg(visit(forNode->startVal, c));
    if (res->error) return res;

    Number<double> *endVal = (Number<double> *) res->reg(visit(forNode->endVal, c));
    if (res->error) return res;

    Number<double> *stepVal = new Number<double>(1, fName, lines[n->line]);

    if (forNode->stepVal) {
        stepVal = (Number<double> *) res->reg(visit(forNode->stepVal, c));
        if (res->error) return res;
    }

    double i = startVal->getValue();

    function<bool()> condition;

    if (stepVal->getValue() >= 0) {
        condition = [&] {
            return i < endVal->getValue();
        };
    } else {
        condition = [&]() {
            return i > endVal->getValue();
        };
    }

    while (condition()) {
        c->symbolTable->set(forNode->varNameTok->getValueObject()->getValue(),
                            new Number<double>(i, fName, lines[n->line]));
        i += stepVal->getValue();

        elements.push_back(res->reg(visit(forNode->body, c)));
        if (res->error) return res;
    }
    BaseValue *val = (new List<vector<BaseValue *>>(elements, fName, lines[n->line]))->setContext(c)->setPos(
            n->posStart, n->posEnd, n->line);
    if (forNode->shouldReturnNull) {
        val = new Number<double>(0, fName, lines[n->line]);
    }
    return res->success(val);
}

RuntimeResult *Interpreter::visitWhileNode(Node *n, Context *c) {
    RuntimeResult *res = new RuntimeResult();
    WhileNode *whileNode = (WhileNode *) n;
    vector<BaseValue *> elements;

    while (true) {
        BaseValue *condition = res->reg(visit(whileNode->condition, c));
        if (res->error) return res;

        if (not condition->isTrue()) break;

        elements.push_back(res->reg(visit(whileNode->body, c)));
        if (res->error) return res;
    }
    BaseValue *val = (new List<vector<BaseValue *>>(elements, fName, lines[n->line]))->setContext(c)->setPos(
            n->posStart, n->posEnd, n->line);
    if (whileNode->shouldReturnNull) {
        val = val = new Number<double>(0, fName, lines[n->line]);
    }
    return res->success(val);
}

RuntimeResult *Interpreter::visitIfNode(Node *n, Context *c) {
    RuntimeResult *res = new RuntimeResult();
    IfNode *node = (IfNode *) n;
    for (auto &ifCase: node->cases) {
        BaseValue *condValue = res->reg(visit(get<0>(ifCase), c));
        Node *expr = get<1>(ifCase);
        if (res->error) return res;

        if (condValue->isTrue()) {
            BaseValue *exprValue = res->reg(visit(expr, c));
            if (res->error) return res;
            return res->success(exprValue);
        }
    }
    if (node->elseCase) {
        BaseValue *elseValue = res->reg(visit(node->elseCase, c));
        if (res->error) return res;
        return res->success(elseValue);
    }
    return res->success(new Number<double>(0, fName, lines[n->line]));
}

RuntimeResult *Interpreter::visitListNode(Node *n, Context *c) {
    RuntimeResult *res = new RuntimeResult();
    vector<BaseValue *> elements;
    ListNode *listNode = (ListNode *) n;

    for (auto element: listNode->elements) {
        elements.push_back(res->reg(visit(element, c)));
        if (res->error) return res;
    }

    return res->success(
            (new List<vector<BaseValue *>>(elements, fName, lines[listNode->line]))->setContext(c)->setPos(n->posStart,
                                                                                                           n->posEnd,
                                                                                                           n->line));
}

RuntimeResult *Interpreter::visitMapNode(Node *n, Context *c) {
    RuntimeResult *res = new RuntimeResult();
    map<BaseValue *, BaseValue *> dict;
    MapNode *mapNode = (MapNode *) n;

    for (auto element: mapNode->dict) {
        BaseValue *key = res->reg(visit(element.first, c));
        if (res->error) return res;
        BaseValue *value = res->reg(visit(element.second, c));
        if (res->error) return res;
        dict[key] = value;
    }

    return res->success(
            (new Map<map<BaseValue *, BaseValue *>>(dict, fName, lines[mapNode->line]))->setContext(c)->setPos(
                    n->posStart, n->posEnd, n->line));
}

RuntimeResult *Interpreter::visitVarAccessNode(Node *n, Context *c) {
    RuntimeResult *result = new RuntimeResult();
    VarAccessNode *node = (VarAccessNode *) n;
    string varName = ((Token<string> *) node->varNameTok)->getValueObject()->getValue();
    BaseValue *value = c->symbolTable->get(varName);

    if (!value) {
        return result->failure(new RuntimeError(
                node->posStart,
                node->posEnd,
                node->line,
                fName,
                lines[node->line],
                varName + " is not defined",
                c
        ));
    }
    value = value->setPos(node->posStart, node->posEnd, node->line);
    if (value->type == T_NUM) {
        ((Number<double> *) value)->setContext(c);
    } else if (value->type == T_STRING) {
        ((String<string> *) value)->setContext(c);
    } else if (value->type == T_FUNC) {
        ((BaseFunction<int> *) value)->setContext(c);
    } else if (value->type == T_LIST) {
        ((List<vector<BaseValue *>> *) value)->setContext(c);
    } else if (value->type == T_MAP) {
        ((Map<map<BaseValue *, BaseValue *>> *) value)->setContext(c);
    }
    return result->success(value);
}

RuntimeResult *Interpreter::visitCallNode(Node *n, Context *c) {
    RuntimeResult *res = new RuntimeResult();
    CallNode *callNode = (CallNode *) n;
    vector<BaseValue *> args;

    BaseFunction<int> *valToCall;
    BaseValue *b = res->reg(visit(callNode->nodeToCall, c));
    if (res->error) return res;
    if (b->type != T_FUNC) {
        return res->failure(new RuntimeError(
                callNode->posStart,
                callNode->posEnd,
                callNode->line,
                fName,
                lines[callNode->line],
                "Can't call non-function",
                c
        ));
    }

    valToCall = dynamic_cast<BaseFunction<int> *>(b);

    valToCall = dynamic_cast<BaseFunction<int> *>(valToCall->copy()->setPos(callNode->posStart, callNode->posEnd,
                                                                            callNode->nodeToCall->line));
    valToCall->callTxt = lines[callNode->nodeToCall->line]; //Update the line func is called on

    for (auto argNode: callNode->args) {
        args.push_back(res->reg(visit(argNode, c)));
        if (res->error) return res;
    }

    BaseValue *returnVal = res->reg(valToCall->execute(args));
    if (res->error) return res;
    returnVal = returnVal->copy()->setPos(callNode->posStart, callNode->posEnd, callNode->line);
    if (returnVal->type == T_NUM) {
        ((Number<double> *) returnVal)->setContext(c);
    } else if (returnVal->type == T_STRING) {
        ((String<string> *) returnVal)->setContext(c);
    } else if (returnVal->type == T_FUNC) {
        ((BaseFunction<int> *) returnVal)->setContext(c);
    } else if (returnVal->type == T_LIST) {
        ((List<vector<BaseValue *>> *) returnVal)->setContext(c);
    } else if (returnVal->type == T_MAP) {
        ((Map<map<BaseValue *, BaseValue *>> *) returnVal)->setContext(c);
    }
    return res->success(returnVal);
}

RuntimeResult *Interpreter::visitFuncDefNode(Node *n, Context *c) {
    RuntimeResult *res = new RuntimeResult();
    FuncDefNode *node = (FuncDefNode *) n;

    string funcName = node->funcNameTok ? node->funcNameTok->getValueObject()->getValue() : "anonymous";
    Node *bodyNode = node->body;

    vector<string> argNames;
    for (auto &argName: node->argNameToks) {
        argNames.push_back(((Token<string> *) argName)->getValueObject()->getValue());
    }

    BaseValue *funcValue = (new Function<int>(fName, lines[node->line], funcName, bodyNode, argNames, lines,
                                              node->shouldReturnNull))
            ->setContext(c)
            ->setPos(node->posStart, node->posEnd, node->line);

    if (node->funcNameTok) {
        c->symbolTable->set(funcName, funcValue);
    }

    return res->success(funcValue);
}

RuntimeResult *Interpreter::visitVarAssignNode(Node *n, Context *c) {
    auto *result = new RuntimeResult();
    auto *node = (VarAssignNode *) n;
    string varName = ((Token<string> *) node->varNameTok)->getValueObject()->getValue();
    BaseValue *value = result->reg(visit(node->valueNode, c));
    if (result->error) return result;
    c->symbolTable->set(varName, value);
    return result->success(value);
}


RuntimeResult *Interpreter::visitNumberNode(Node *n, Context *c) {
    NumberNode *node = (NumberNode *) n;
    Number<double> *num = (Number<double> *) (new Number<double>(node->token->getValueObject()->getValue(), fName,
                                                                 lines[node->token->line]))->setContext(c)->setPos(
            node->token->posStart,
            node->token->posEnd,
            node->token->line
    );
    //cout << num->numValue << endl;
    return (new RuntimeResult())->success(num);
}

RuntimeResult *Interpreter::visitStringNode(Node *n, Context *c) {
    StringNode *node = (StringNode *) n;
    String<string> *str = (String<string> *) (new String<string>(node->token->getValueObject()->getValue(), fName,
                                                                 lines[node->token->line]))->setContext(c)->setPos(
            node->token->posStart,
            node->token->posEnd,
            node->token->line
    );
    return (new RuntimeResult())->success(str);
}

RuntimeResult *Interpreter::visitBinOpNode(Node *n, Context *c) {
    RuntimeResult *rtRes = new RuntimeResult();
    BinaryOperationNode *node = (BinaryOperationNode *) n;
    BaseValue *left = rtRes->reg(visit(node->getLeft(), c));
    if (rtRes->error) return rtRes;
    BaseValue *right = rtRes->reg(visit(node->getRight(), c));
    if (rtRes->error) return rtRes;
    BaseValue *result = new BaseValue(left->type, fName, lines[node->opTok->line]);

    if (node->opTok->type == PLUS) {
        result = left->add(right);
    } else if (node->opTok->type == MINUS) {
        result = left->subtract(right);
    } else if (node->opTok->type == MULTIPLY) {
        result = left->multiply(right);
    } else if (node->opTok->type == DIVIDE) {
        result = left->divide(right);
    } else if (node->opTok->type == POWER) {
        result = left->power(right);
    } else if (node->opTok->type == MOD) {
        result = left->mod(right);
    } else if (node->opTok->getType() == GREATER_THAN) {
        result = left->compGreaterThan(right);
    } else if (node->opTok->getType() == GREATER_THAN_EQUAL) {
        result = left->compGreaterThanEquals(right);
    } else if (node->opTok->getType() == LESS_THAN) {
        result = left->compLessThan(right);
    } else if (node->opTok->getType() == LESS_THAN_EQUAL) {
        result = left->compLessThanEquals(right);
    } else if (node->opTok->getType() == NOT_EQUAL) {
        result = left->compNotEquals(right);
    } else if (node->opTok->getType() == EQUAL_EQUAL) {
        result = left->compEquals(right);
    } else if (node->opTok->getType() == PLUS_EQUAL) {
        result = left->plusEquals(right);
    } else if (node->opTok->getType() == MINUS_EQUAL) {
        result = left->minusEquals(right);
    } else if (node->opTok->getType() == ARROW) {
        result = left->getIdentifier(right);
    } else if (node->opTok->getType() == AND) {
        result = left->andedBy(right);
    } else if (node->opTok->getType() == OR) {
        result = left->oredBy(right);
    } else if (node->opTok->getType() == GET) {
        result = left->get(right);
    }
    //TODO: Update this area for any errors
    if (left->type == T_NUM) {
        if (((Number<double> *) left)->rtError) {
            RuntimeResult *r = rtRes->failure(((Number<double> *) left)->rtError);
            ((Number<double> *) left)->rtError = nullptr;
            return r;
        }
    } else if (left->type == T_STRING) {
        if (((String<string> *) left)->rtError) {
            RuntimeResult *r = rtRes->failure(((String<string> *) left)->rtError);
            ((String<string> *) left)->rtError = nullptr;
            return r;
        }
    } else if (left->type == T_FUNC) {
        if (((BaseFunction<int> *) left)->rtError) {
            RuntimeResult *r = rtRes->failure(((BaseFunction<int> *) left)->rtError);
            ((BaseFunction<int> *) left)->rtError = nullptr;
            return r;
        }
    } else if (left->type == T_LIST) {
        if (((List<vector<BaseValue *>> *) left)->rtError) {
            RuntimeResult *r = rtRes->failure(((List<vector<BaseValue *>> *) left)->rtError);
            ((List<vector<BaseValue *>> *) left)->rtError = nullptr;
            return r;
        }
    } else if (left->type == T_MAP) {
        if (((Map<map<BaseValue *, BaseValue *>> *) left)->rtError) {
            RuntimeResult *r = rtRes->failure(((Map<map<BaseValue *, BaseValue *>> *) left)->rtError);
            ((Map<map<BaseValue *, BaseValue *>> *) left)->rtError = nullptr;
            return r;
        }
    }

    //cout << result->toString() << endl;

    return rtRes->success(result->setPos(n->posStart, n->posEnd, n->line));

}

RuntimeResult *Interpreter::visitUnaryOpNode(Node *n, Context *c) {
    RuntimeResult *rtRes = new RuntimeResult();
    UnaryOperationNode *opNode = (UnaryOperationNode *) n;
    Number<double> *num = (Number<double> *) rtRes->reg(visit(opNode->node, c));

    if (rtRes->error) return rtRes;


    if (opNode->op->type == MINUS) {
        num = num->multiply(new Number<double>(-1, num->fName, num->fTxt));
    } else if (opNode->op->type == NOT) {
        num = dynamic_cast<Number<double> *>(num->notted());
    }

    if (num->rtError) return rtRes->failure(num->rtError);

    return rtRes->success(num->setPos(n->posStart, n->posEnd, n->line));
}