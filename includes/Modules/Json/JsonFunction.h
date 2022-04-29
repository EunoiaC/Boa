//
// Created by Preeti Thorat on 3/21/22.
//

#ifndef BOA_JSONFUNCTION_H
#define BOA_JSONFUNCTION_H

#include "../../Values/Functions/BaseFunction.h"
#include "../../Values/String/String.h"
#include "../../Values/Map/Map.h"

template<typename T> class JsonFunction : public BaseFunction<T> {
public:
    typedef RuntimeResult * (JsonFunction<int>::*FnPtr)(Context * execCtx);
    map<string, FnPtr> funcMap;
    vector<BaseValue *> args;
    map<string, BaseValue *> defaultArgs;
    JsonFunction<T>(string name, vector<string> argNames, map<string, BaseValue *> defaultArgs, string fName, string fTxt);
    RuntimeResult * execute(vector<BaseValue*> args) override;
    JsonFunction<int> *copy() override;

    RuntimeResult * execute_loads(Context * execCtx);

    string toString() override;
};


#endif //BOA_JSONFUNCTION_H
