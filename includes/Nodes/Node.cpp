//
// Created by Aadi Yadav on 11/7/21.
//

#include "Node.h"

static const string N_NUMBER = "NUMBER_NODE";
static const string N_BINOP = "BINOP_NODE";
static const string N_UNOP = "UNARY_OP_NODE";
static const string N_VAR_ACCESS = "VAR_ACCESS_NODE";
static const string N_VAR_ASSIGN = "VAR_ASSIGN_NODE";
static const string N_VAR_OPERATION = "N_VAR_OPERATION";
static const string N_IF = "IF_NODE";
static const string N_FOR = "FOR_NODE";
static const string N_WHILE = "WHILE_NODE";

Node::Node(string type) {
    this->type = type;
}

string Node::toString() {
    return "";
}

