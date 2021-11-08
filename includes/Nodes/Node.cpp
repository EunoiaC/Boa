//
// Created by Preeti Thorat on 11/7/21.
//

#include "Node.h"

static const string N_NUMBER = "NUMBER_NODE";
static const string N_BINOP = "BINOP_NODE";

Node::Node(string type) {
    this->type = type;
}

