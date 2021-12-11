//
// Created by Aadi Yadav on 11/7/21.
//

#ifndef BOA_NODE_H
#define BOA_NODE_H

#include <string>

using namespace std;

static const string N_NUMBER = "NUMBER_NODE";
static const string N_STRING = "STRING_NODE";
static const string N_BINOP = "BINOP_NODE";
static const string N_UNOP = "UNARY_OP_NODE";
static const string N_VAR_ACCESS = "VAR_ACCESS_NODE";
static const string N_VAR_ASSIGN = "VAR_ASSIGN_NODE";
static const string N_VAR_OPERATION = "N_VAR_OPERATION";
static const string N_IF = "IF_NODE";
static const string N_FOR = "FOR_NODE";
static const string N_WHILE = "WHILE_NODE";
static const string N_FUNC_DEF = "FUNC_DEF_NODE";
static const string N_CALL = "CALL_NODE";

class Node {
public:
    Node(string type);

    /**
     * Type of the node
     */
    int posStart, posEnd, line;
    string type;

    virtual string toString();
};


#endif //BOA_NODE_H
