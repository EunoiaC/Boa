//
// Created by Preeti Thorat on 2/3/22.
//

#ifndef BOA_CLASSFUNCTION_H
#define BOA_CLASSFUNCTION_H

#include <vector>
#include "../../Nodes/Node.h"
#include "../Functions/BaseFunction.h"
#include "../../RuntimeResult/RuntimeResult.h"

template<typename T>
class ClassFunction : public BaseFunction<T> {
public:
    Node *body;
    vector<string> lines;
    bool autoReturn;
    string className;
    Context *classCtx;

    ClassFunction<T>(string fName, string fTxt, string name, Node *body, vector<string> argNames,
                     map<string, BaseValue *> defaultArgs, vector<string> lines, bool autoReturn, Context *context, string className);

    RuntimeResult *execute(vector<BaseValue *> args) override;

    ClassFunction<int> *copy() override;

    string toString() override;
};


#endif //BOA_CLASSFUNCTION_H
