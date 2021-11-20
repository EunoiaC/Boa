//
// Created by Preeti Thorat on 11/20/21.
//

#include "Interpreter.h"

//TODO: In areas with (0, 0) as params, fix the code to use the correct values

Interpreter::Interpreter() {
    funcMap[N_UNOP] = &Interpreter::visitUnaryOpNode;
    funcMap[N_BINOP] = &Interpreter::visitBinOpNode;
    funcMap[N_NUMBER] = &Interpreter::visitNumberNode;
}

BaseValue *Interpreter::visit(Node *n) {
    string methodName = n->type;
    return (this->*funcMap[methodName])(n);
}

BaseValue *Interpreter::visitNumberNode(Node *n) {
    NumberNode *node = (NumberNode *) n;
    Number * num = (new Number(node->token->getValueObject()->getValue()))->setPos(node->token->posStart, node->token->posEnd);
    //cout << num->numValue << endl;
    return num;
}

BaseValue *Interpreter::visitBinOpNode(Node *n) {
    BinaryOperationNode *node = (BinaryOperationNode *) n;
    BaseValue *left = (Number *) visit(node->getLeft());
    BaseValue *right = (Number *) visit(node->getRight());

    Number * result = new Number(0);

    if (node->opTok->type == PLUS) {
        result = ((Number *) left)->add((Number *) right);
    } else if (node->opTok->type == MINUS) {
        result = ((Number *) left)->subtract((Number *) right);
    } else if (node->opTok->type == MULTIPLY) {
        result = ((Number *) left)->multiply((Number *) right);
    } else if (node->opTok->type == DIVIDE) {
        result = ((Number *) left)->divide((Number *) right);
    }
    return result->setPos(n->posStart, n->posEnd);

}

BaseValue *Interpreter::visitUnaryOpNode(Node *n) {
    UnaryOperationNode * opNode = (UnaryOperationNode *) n;
    Number * num = (Number*) visit(opNode->node);

    if(opNode->op->type == MINUS){
        num = num->multiply(new Number(-1));
    }

    return num->setPos(n->posStart, n->posEnd);
}