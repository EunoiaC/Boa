//
// Created by Preeti Thorat on 12/9/21.
//

#ifndef BOA_FUNCTION_H
#define BOA_FUNCTION_H

#include <vector>
#include "../../Nodes/Node.h"
#include "../BaseValues/Value.h"
#include "../../RuntimeResult/RuntimeResult.h"

using namespace std;

template<typename T> class Function : public Value<T> {
public:
    string name, callTxt;
    vector<string> argNames;
    Node *body;
    vector<string> lines;

    Function<T>(string fName, string fTxt, string name, Node *body, vector<string> argNames, vector<string> lines);

    RuntimeResult *execute(vector<BaseValue *> args) override;

    Function<int> *copy();

    string toString() override;
};


#endif //BOA_FUNCTION_H
