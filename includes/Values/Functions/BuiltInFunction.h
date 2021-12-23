//
// Created by Preeti Thorat on 12/22/21.
//

#ifndef BOA_BUILTINFUNCTION_H
#define BOA_BUILTINFUNCTION_H

#include "BaseFunction.h"
#include "../String.h"

template<typename T> class BuiltInFunction : public BaseFunction<T> {
public:
    typedef RuntimeResult * (BuiltInFunction<int>::*FnPtr)(Context * execCtx);
    map<string, FnPtr> funcMap;
    BuiltInFunction<T>(string name, vector<string> argNames, string fName, string fTxt);
    RuntimeResult * execute(vector<BaseValue*> args) override;
    BuiltInFunction<int> *copy() override;

    RuntimeResult * execute_print(Context * execCtx);
    RuntimeResult * execute_input(Context * execCtx);

    string toString() override;
};


#endif //BOA_BUILTINFUNCTION_H
