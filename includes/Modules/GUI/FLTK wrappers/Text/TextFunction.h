//
// Created by Preeti Thorat on 7/18/22.
//

#ifndef BOA_TEXTFUNCTION_H
#define BOA_TEXTFUNCTION_H


#include "../../../../Values/Functions/BaseFunction.h"
#include <fstream>
#include "../../../../Values/List/List.h"
#include "../../../../Values/Functions/Function.h"
#include "Text.h"

template<typename T> class TextFunction : public BaseFunction<T> {
public:
    typedef RuntimeResult * (TextFunction<int>::*FnPtr)(Context * execCtx);
    map<string, FnPtr> funcMap;
    vector<BaseValue *> args;
    map<string, BaseValue *> defaultArgs;
    Text<int> * txtObj;
    TextFunction<T>(Text<int> * txtObj, string name, vector<string> argNames, map<string, BaseValue *> defaultArgs, string fName, string fTxt);
    RuntimeResult * execute(vector<BaseValue*> args, map<string, BaseValue *> kwargs) override;
    TextFunction<int> *copy() override;

    RuntimeResult * execute_setText(Context * execCtx);

    string toString() override;
};


#endif //BOA_TEXTFUNCTION_H
