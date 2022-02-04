//
// Created by Preeti Thorat on 12/9/21.
//

#ifndef BOA_FUNCTION_H
#define BOA_FUNCTION_H

#include "../../Nodes/Node.h"
#include "BaseFunction.h"
#include "../../RuntimeResult/RuntimeResult.h"

template<typename T> class Function : public BaseFunction<T> {
public:
    Node *body;
    vector<string> lines;
    bool autoReturn;

    Function<T>(string fName, string fTxt, string name, Node *body, vector<string> argNames, map<string, BaseValue *> defaultArgs, vector<string> lines, bool autoReturn);

    RuntimeResult *execute(vector<BaseValue *> args) override;

    Function<int> *copy() override;

    string toString() override;
};


#endif //BOA_FUNCTION_H