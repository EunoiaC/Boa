//
// Created by Preeti Thorat on 11/20/21.
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
}

RuntimeResult *Interpreter::visit(Node *n, Context *c) {
    string methodName = n->type;
    return (this->*funcMap[methodName])(n, c);
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
    return result->success(value);
}

RuntimeResult *Interpreter::visitVarAssignNode(Node *n, Context *c) {
    auto *result = new RuntimeResult();
    auto *node = (VarAssignNode *) n;
    string varName = ((Token<string> *) node->varNameTok)->getValueObject()->getValue();
    BaseValue *value = result->reg(visit(node->valueNode, c));

    if(result->error) return result;
    c->symbolTable->set(varName, value);
    return result->success(value);
}


RuntimeResult *Interpreter::visitNumberNode(Node *n, Context *c) {
    NumberNode *node = (NumberNode *) n;
    Number *num = (new Number(node->token->getValueObject()->getValue(), fName,
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
    Number *result = new Number(0, fName, lines[node->opTok->line]);

    if (node->opTok->type == PLUS) {
        result = ((Number *) left)->add(right);
    } else if (node->opTok->type == MINUS) {
        result = ((Number *) left)->subtract(right);
    } else if (node->opTok->type == MULTIPLY) {
        result = ((Number *) left)->multiply(right);
    } else if (node->opTok->type == DIVIDE) {
        result = ((Number *) left)->divide(right);
    } else if (node->opTok->type == POWER) {
        result = ((Number *) left)->power(right);
    } else if (node->opTok->type == MOD) {
        result = ((Number *) left)->mod(right);
    }

    if (result->rtError) return rtRes->failure(result->rtError);
    return rtRes->success(result->setPos(n->posStart, n->posEnd, n->line));

}

RuntimeResult *Interpreter::visitUnaryOpNode(Node *n, Context *c) {
    RuntimeResult *rtRes = new RuntimeResult();
    UnaryOperationNode *opNode = (UnaryOperationNode *) n;
    Number *num = (Number *) rtRes->reg(visit(opNode->node, c));

    if (rtRes->error) return rtRes;


    if (opNode->op->type == MINUS) {
        num = num->multiply(new Number(-1, num->fName, num->fTxt));
    }

    if (num->rtError) return rtRes->failure(num->rtError);

    return rtRes->success(num->setPos(n->posStart, n->posEnd, n->line));
}