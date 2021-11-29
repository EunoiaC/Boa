//
// Created by Preeti Thorat on 11/20/21.
//

#ifndef BOA_INTERPRETER_H
#define BOA_INTERPRETER_H
#include "../Values/Number.cpp"
#include "../RuntimeResult/RuntimeResult.cpp"

class Interpreter {
public:
    string fName;
    vector<string> lines;
    //Change typedef with return type of function
    typedef RuntimeResult * (Interpreter::*FnPtr)(Node* n, Context* c);
    map<string, FnPtr> funcMap;
    Interpreter(string name, vector<string> l);
    RuntimeResult * visit(Node * n, Context * c);
    RuntimeResult * visitNumberNode(Node * n, Context* c);
    RuntimeResult * visitBinOpNode(Node * n, Context* c);
    RuntimeResult * visitUnaryOpNode(Node * n, Context* c);
    RuntimeResult * visitVarAssignNode(Node * n, Context* c);
    RuntimeResult * visitVarAccessNode(Node * n, Context* c);
    RuntimeResult * visitVarOperationNode(Node * n, Context* c);
};


#endif //BOA_INTERPRETER_H
