//
// Created by Preeti Thorat on 12/22/21.
//

#ifndef BOA_BUILTINFUNCTION_H
#define BOA_BUILTINFUNCTION_H

#include "BaseFunction.h"
#include "../String/String.h"
#include "../List/List.h"
#include "../Map.h"
#include <iostream>

template<typename T> class BuiltInFunction : public BaseFunction<T> {
public:
    typedef RuntimeResult * (BuiltInFunction<int>::*FnPtr)(Context * execCtx);
    map<string, FnPtr> funcMap;
    vector<BaseValue *> args;
    map<string, BaseValue *> defaultArgs;
    BuiltInFunction<T>(string name, vector<string> argNames, map<string, BaseValue *> defaultArgs, string fName, string fTxt);
    RuntimeResult * execute(vector<BaseValue*> args) override;
    BuiltInFunction<int> *copy() override;

    RuntimeResult * execute_print(Context * execCtx);
    RuntimeResult * execute_input(Context * execCtx);
    RuntimeResult * execute_toNum(Context * execCtx);
    RuntimeResult * execute_toStr(Context * execCtx);
    RuntimeResult * execute_lenOf(Context * execCtx);
    RuntimeResult * execute_instanceOf(Context * execCtx);
    RuntimeResult * execute_eval(Context * execCtx);
    RuntimeResult * execute_rename(Context * execCtx);
    RuntimeResult * execute_getSymbolTable(Context * execCtx);

    string toString() override;
};


#endif //BOA_BUILTINFUNC