//
// Created by Aadi Yadav on 11/28/21.
//

#include "VarOperationNode.h"

VarOperationNode::VarOperationNode(BaseToken *token, Node *node, string operation) : Node(N_VAR_OPERATION){
    this->var = token;
    this->value = node;
    this->op = operation;
}