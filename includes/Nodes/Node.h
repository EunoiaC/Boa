//
// Created by Aadi Yadav on 11/7/21.
//

#ifndef BOA_NODE_H
#define BOA_NODE_H

#include <string>

using namespace std;

static const string N_NUMBER = "NUMBER_NODE";
static const string N_STRING = "STRING_NODE";
static const string N_LIST = "LIST_NODE";
static const string N_MAP = "MAP_NODE";
static const string N_BINOP = "BINOP_NODE";
static const string N_UNOP = "UNARY_OP_NODE";
static const string N_VAR_ACCESS = "VAR_ACCESS_NODE";
static const string N_VAR_ASSIGN = "VAR_ASSIGN_NODE";
static const string N_VAR_OPERATION = "N_VAR_OPERATION";
static const string N_IF = "IF_NODE";
static const string N_FOR = "FOR_NODE";
static const string N_ITER = "ITER_NODE";
static const string N_WHILE = "WHILE_NODE";
static const string N_FUNC_DEF = "FUNC_DEF_NODE";
static const string N_CLASS_DEF = "CLASS_DEF_NODE";
static const string N_CALL = "CALL_NODE";
static const string N_RETURN = "RETURN_NODE";
static const string N_BREAK = "BREAK_NODE";
static const string N_CONTINUE = "CONTINUE_NODE";
static const string N_IMPORT = "IMPORT_NODE";
static const string N_IDX = "INDEX_NODE";
static const string N_TRY_CATCH = "TRY_CATCH_NODE";
static const string N_EITHER = "EITHER_NODE";
static const string N_AWAIT = "AWAIT_NODE";

class Node {
public:
    Node(string type);

    /**
     * Type of the node
     */
    int posStart, posEnd, line;
    string type;
    string fName, fTxt;

    virtual string toString();
};


#endif //BOA_NODE_H
