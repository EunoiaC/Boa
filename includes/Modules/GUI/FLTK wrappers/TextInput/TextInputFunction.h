//
// Created by Preeti Thorat on 7/10/22.
//

#ifndef BOA_TEXTINPUTFUNCTION_H
#define BOA_TEXTINPUTFUNCTION_H


#include "../../../../Values/Functions/BaseFunction.h"
#include <fstream>
#include "../../../../Values/List/List.h"
#include "../../../../Values/Functions/Function.h"
#include "TextInput.h"

template<typename T> class TextInputFunction : public BaseFunction<T> {
public:
    typedef RuntimeResult * (TextInputFunction<int>::*FnPtr)(Context * execCtx);
    map<string, FnPtr> funcMap;
    vector<BaseValue *> args;
    map<string, BaseValue *> defaultArgs;
    TextInput<int> * inObj;
    TextInputFunction<T>(TextInput<int> * inObj, string name, vector<string> argNames, map<string, BaseValue *> defaultArgs, string fName, string fTxt);
    RuntimeResult * execute(vector<BaseValue*> args, map<string, BaseValue *> kwargs) override;
    TextInputFunction<int> *copy() override;

    RuntimeResult * execute_setCallback(Context * execCtx);

    string toString() override;
};

#endif //BOA_TEXTINPUTFUNCTION_H
