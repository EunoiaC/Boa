//
// Created by Preeti Thorat on 12/9/21.
//

#ifndef BOA_FUNCTION_H
#define BOA_FUNCTION_H

#include <vector>
#include "../Interpreter/Interpreter.h"

class Function : public Value<int> {
public:
    string name, callTxt;
    vector<string> argNames;
    Node *body;
    vector<string> lines;

    Function(string fName, string fTxt, string name, Node *body, vector<string> argNames, vector<string> lines);

    RuntimeResult *execute(vector<BaseValue *> args) override;

    Function *copy();

    string toString() override;
};


#endif //BOA_FUNCTION_H
