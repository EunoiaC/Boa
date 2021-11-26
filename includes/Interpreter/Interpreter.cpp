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
}

RuntimeResult *Interpreter::visit(Node *n, Context *c) {
    string methodName = n->type;
    return (this->*funcMap[methodName])(n, c);
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
        result = ((Number *) left)->add((Number *) right);
    } else if (node->opTok->type == MINUS) {
        result = ((Number *) left)->subtract((Number *) right);
    } else if (node->opTok->type == MULTIPLY) {
        result = ((Number *) left)->multiply((Number *) right);
    } else if (node->opTok->type == DIVIDE) {
        result = ((Number *) left)->divide((Number *) right);
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