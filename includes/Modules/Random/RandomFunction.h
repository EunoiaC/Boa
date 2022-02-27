//
// Created by Preeti Thorat on 1/28/22.
//

#ifndef BOA_RANDOMFUNCTION_H
#define BOA_RANDOMFUNCTION_H

#include "../../Values/Functions/BaseFunction.h"
#include <algorithm>
#include <random>
#include "../../Values/List/List.h"

template<typename T> class RandomFunction : public BaseFunction<T> {
public:
    typedef RuntimeResult * (RandomFunction<int>::*FnPtr)(Context * execCtx);
    map<string, FnPtr> funcMap;
    vector<BaseValue *> args;
    map<string, BaseValue *> defaultArgs;
    RandomFunction<T>(string name, vector<string> argNames, map<string, BaseValue *> defaultArgs, string fName, string fTxt);
    RuntimeResult * execute(vector<BaseValue*> args) override;
    RandomFunction<int> *copy() override;

    RuntimeResult * execute_randrange(Context * execCtx);
    RuntimeResult * execute_choose(Context * execCtx);
    RuntimeResult * execute_shuffle(Context * execCtx);

    string toString() override;
};


#endif //BOA_RANDOMFUNCTION_H
