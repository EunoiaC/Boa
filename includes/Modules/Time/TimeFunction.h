//
// Created by Preeti Thorat on 4/16/22.
//

#ifndef BOA_TIMEFUNCTION_H
#define BOA_TIMEFUNCTION_H


#include "../../Values/Functions/BaseFunction.h"
#include "../../Values/List/List.h"

template<typename T> class TimeFunction : public BaseFunction<T> {
public:
    typedef RuntimeResult * (TimeFunction<int>::*FnPtr)(Context * execCtx);
    map<string, FnPtr> funcMap;
    vector<BaseValue *> args;
    map<string, BaseValue *> defaultArgs;
    TimeFunction<T>(string name, vector<string> argNames, map<string, BaseValue *> defaultArgs, string fName, string fTxt);
    RuntimeResult * execute(vector<BaseValue*> args) override;
    TimeFunction<int> *copy() override;

    RuntimeResult * execute_waitMs(Context * execCtx);
    RuntimeResult * execute_waitSec(Context * execCtx);

    string toString() override;
};


#endif //BOA_TIMEFUNCTION_H
