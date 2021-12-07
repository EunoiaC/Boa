//
// Created by Aadi Yadav on 11/20/21.
//

#include "Interpreter.h"

Interpreter::Interpreter(string name, vector<string> l) {
    fName = name;
    lines = l;
    funcMap[N_UNOP] = &Interpreter::visitUnaryOpNode;
    funcMap[N_BINOP] = &Interpreter::visitBinOpNode;
    funcMap[N_NUMBER] = &Interpreter::visitNumberNode;
    funcMap[N_VAR_ACCESS] = &Interpreter::visitVarAccessNode;
    funcMap[N_VAR_ASSIGN] = &Interpreter::visitVarAssignNode;
    funcMap[N_VAR_OPERATION] = &Interpreter::visitVarOperationNode;
    funcMap[N_IF] = &Interpreter::visitIfNode;
    funcMap[N_FOR] = &Interpreter::visitForNode;
    funcMap[N_WHILE] = &Interpreter::visitWhileNode;
}

RuntimeResult *Interpreter::visit(Node *n, Context *c) {
    string methodName = n->type;
    return (this->*funcMap[methodName])(n, c);
}

RuntimeResult *Interpreter::visitForNode(Node *n, Context *c) {
    RuntimeResult *res = new RuntimeResult();
    ForNode *forNode = (ForNode *) n;

    Number *startVal = (Number*) res->reg(visit(forNode->startVal, c));
    if (res->error) return res;

    Number *endVal = (Number*) res->reg(visit(forNode->endVal, c));
    if (res->error) return res;

    Number *stepVal = new Number(1, fName, lines[n->line]);

    if (forNode->stepVal) {
        stepVal = (Number*) res->reg(visit(forNode->stepVal, c));
        if (res->error) return res;
    }

    double i = startVal->getValue();

    function<bool()> condition;

    if(stepVal->getValue() >= 0) {
        condition = [&]{
            return i < endVal->getValue();
        };
    } else{
        condition = [&]() {
            return i > endVal->getValue();
        };
    }

    while(condition()) {
        c->symbolTable->set(forNode->varNameTok->getValueObject()->getValue(), new Number(i, fName, lines[n->line]));
        i += stepVal->getValue();

        res->reg(visit(forNode->body, c));
        if(res->error) return res;
    }
    return res->success(nullptr);
}

RuntimeResult *Interpreter::visitWhileNode(Node *n, Context *c) {
    RuntimeResult *res = new RuntimeResult();
    WhileNode *whileNode = (WhileNode *) n;

    while(true){
        BaseValue * condition = res->reg(visit(whileNode->condition, c));
        if(res->error) return res;

        if(not condition->isTrue()) break;

        res->reg(visit(whileNode->body, c));
        if(res->error) return res;
    }
    return res->success(nullptr);
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
    return res->success(nullptr);
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
    return result->success(value);
}

RuntimeResult *Interpreter::visitVarOperationNode(Node *n, Context *c) {
    RuntimeResult *result = new RuntimeResult();
    VarOperationNode *node = (VarOperationNode *) n;
    string varName = ((Token<string> *) node->var)->getValueObject()->getValue();
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

    BaseValue *finValue = nullptr;

    if (node->op == PLUS_EQUAL || node->op == MINUS_EQUAL) {
        if (value->type == T_NUM) {
            Number *toAdd = (Number *) result->reg(visit(node->value, c));
            if (result->error) return result;
            if (node->op == MINUS_EQUAL) {
                toAdd = toAdd->multiply(new Number(-1, fName, ""));
            }
            finValue = ((Number *) value)->add(toAdd);
            c->symbolTable->set(varName, finValue);
        }
    } else if (node->op == PLUS_PLUS || node->op == MINUS_MINUS) {
        if (value->type == T_NUM) {
            BaseValue *toAdd = new Number(1, fName, "");
            if (node->op == MINUS_MINUS) {
                toAdd = ((Number *) toAdd)->multiply(new Number(-1, fName, ""));
            }
            finValue = ((Number *) value)->add(toAdd);
            c->symbolTable->set(varName, finValue);
        }
    }
    return result->success(finValue);
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
    Number *num = (Number *) (new Number(node->token->getValueObject()->getValue(), fName,
                                         lines[node->token->line]))->setContext(c)->setPos(
            node->token->posStart,
            node->token->posEnd,
            node->token->line
    );
    //cout << num->numValue << endl;
    return (new RuntimeResult())->success(num);
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
    } else if (node->opTok->getType() == AND) {
        result = left->andedBy(right);
    } else if (node->opTok->getType() == OR) {
        result = left->oredBy(right);
    }

    if (((Number *) result)->rtError) return rtRes->failure(((Number *) result)->rtError);
    return rtRes->success(result->setPos(n->posStart, n->posEnd, n->line));

}

RuntimeResult *Interpreter::visitUnaryOpNode(Node *n, Context *c) {
    RuntimeResult *rtRes = new RuntimeResult();
    UnaryOperationNode *opNode = (UnaryOperationNode *) n;
    Number *num = (Number *) rtRes->reg(visit(opNode->node, c));

    if (rtRes->error) return rtRes;


    if (opNode->op->type == MINUS) {
        num = num->multiply(new Number(-1, num->fName, num->fTxt));
    } else if (opNode->op->type == NOT) {
        num = dynamic_cast<Number *>(num->notted());
    }

    if (num->rtError) return rtRes->failure(num->rtError);

    return rtRes->success(num->setPos(n->posStart, n->posEnd, n->line));
}