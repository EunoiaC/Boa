//
// Created by Preeti Thorat on 6/21/22.
//

#ifndef BOA_WINDOWFUNCTION_H
#define BOA_WINDOWFUNCTION_H

#include "../../../../Values/Functions/BaseFunction.h"
#include <fstream>
#include "../../../../Values/List/List.h"
#include "../../../../Values/Functions/Function.h"
#include "Window.h"

template<typename T> class WindowFunction : public BaseFunction<T> {
public:
    typedef RuntimeResult * (WindowFunction<int>::*FnPtr)(Context * execCtx);
    map<string, FnPtr> funcMap;
    vector<BaseValue *> args;
    map<string, BaseValue *> defaultArgs;
    Window<int> * winObj;
    WindowFunction<T>(Window<int> * winObj, string name, vector<string> argNames, map<string, BaseValue *> defaultArgs, string fName, string fTxt);
    RuntimeResult * execute(vector<BaseValue*> args, map<string, BaseValue *> kwargs) override;
    WindowFunction<int> *copy() override;

    RuntimeResult * execute_start(Context * execCtx);

    string toString() override;
};


#endif //BOA_WINDOWFUNCTION_H
