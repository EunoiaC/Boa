//
// Created by Preeti Thorat on 6/21/22.
//

#ifndef BOA_WINDOWFUNCTION_H
#define BOA_WINDOWFUNCTION_H

#include "../../../../Values/Functions/BaseFunction.h"
#include <fstream>
#include "../../../../Values/List/List.h"
#include "../../../../Values/Functions/Function.h"
#include "WindowObj.h"
#include "../Text/Text.h"
#include "../TextInput/TextInput.h"

template<typename T> class WindowFunction : public BaseFunction<T> {
public:
    typedef RuntimeResult * (WindowFunction<int>::*FnPtr)(Context * execCtx);
    map<string, FnPtr> funcMap;
    vector<BaseValue *> args;
    map<string, BaseValue *> defaultArgs;
    WindowObj<int> * winObj;
    WindowFunction<T>(WindowObj<int> * winObj, string name, vector<string> argNames, map<string, BaseValue *> defaultArgs, string fName, string fTxt);
    RuntimeResult * execute(vector<BaseValue*> args, map<string, BaseValue *> kwargs) override;
    WindowFunction<int> *copy() override;

    RuntimeResult * execute_add(Context * execCtx);
    RuntimeResult * execute_start(Context * execCtx);

    string toString() override;
};


#endif //BOA_WINDOWFUNCTION_H
