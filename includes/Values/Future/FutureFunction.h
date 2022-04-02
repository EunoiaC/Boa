//
// Created by Preeti Thorat on 4/2/22.
//

#ifndef BOA_FUTUREFUNCTION_H
#define BOA_FUTUREFUNCTION_H

#include "../Functions/BaseFunction.h"
#include "../List/List.h"
#include "Future.h"

template<typename T> class FutureFunction : public BaseFunction<T> {
public:
    typedef RuntimeResult * (FutureFunction<int>::*FnPtr)(Context * execCtx);
    map<string, FnPtr> funcMap;
    vector<BaseValue *> args;
    map<string, BaseValue *> defaultArgs;
    Future<shared_future<RuntimeResult *>> * value;
    FutureFunction<T>(Future<shared_future<RuntimeResult *>> * value, string name, vector<string> argNames, map<string, BaseValue *> defaultArgs, string fName, string fTxt);
    RuntimeResult * execute(vector<BaseValue*> args) override;
    FutureFunction<int> *copy() override;

    RuntimeResult * execute_get(Context * execCtx);

    string toString() override;
};


#endif //BOA_FUTUREFUNCTION_H
