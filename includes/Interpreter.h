//
// Created by Preeti Thorat on 11/20/21.
//

#ifndef BOA_INTERPRETER_H
#define BOA_INTERPRETER_H
#include "Values/Number.cpp"

class Interpreter {
public:
    //Change typedef with return type of function
    typedef BaseValue * (Interpreter::*FnPtr)(Node* n);
    map<string, FnPtr> funcMap;
    Interpreter();
    BaseValue * visit(Node * n);
    BaseValue * visitNumberNode(Node * n);
    BaseValue * visitBinOpNode(Node * n);
    BaseValue * visitUnaryOpNode(Node * n);
};


#endif //BOA_INTERPRETER_H
