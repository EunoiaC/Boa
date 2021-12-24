//
// Created by Preeti Thorat on 12/9/21.
//

#ifndef BOA_FUNCTION_H
#define BOA_FUNCTION_H

#include <vector>
#include "../../Nodes/Node.h"
#include "BaseFunction.h"
#include "../../RuntimeResult/RuntimeResult.h"

using namespace std;

template<typename T> class Function : public BaseFunction<T> {
public:
    Node *body;
    vector<string> lines;
    bool shouldReturnNull;

    Function<T>(string fName, string fTxt, string name, Node *body, vector<string> argNames, vector<string> lines, bool shouldReturnNull);

    RuntimeResult *execute(vector<BaseValue *> args) override;

    Function<int> *copy() override;

    string toString() override;
};


#endif //BOA_FUNCTION_H