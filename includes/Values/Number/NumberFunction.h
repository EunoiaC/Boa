//
// Created by Preeti Thorat on 1/20/22.
//

#ifndef BOA_NUMBERFUNCTION_H
#define BOA_NUMBERFUNCTION_H

#include "../Functions/BaseFunction.h"

template<typename T> class NumberFunction : public BaseFunction<T>{
public:
    typedef RuntimeResult * (NumberFunction<int>::*FnPtr)(Context * execCtx);
    map<string, FnPtr> funcMap;
    vector<BaseValue *> args;
    map<string, BaseValue *> defaultArgs;
    Number<double>* value;
    NumberFunction<T>(Number<double>* value, string name, vector<string> argNames, map<string, BaseValue *> defaultArgs, string fName, string fTxt);
    RuntimeResult * execute(vector<BaseValue*> args, map<string, BaseValue *> kwargs) override;
    NumberFunction<int> *copy() override;

    RuntimeResult * execute_ceil(Context * execCtx);
    RuntimeResult * execute_floor(Context * execCtx);

    string toString() override;
};


#endif //BOA_NUMBERFUNCTION_H
