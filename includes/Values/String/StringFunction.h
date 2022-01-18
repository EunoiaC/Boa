//
// Created by Preeti Thorat on 1/17/22.
//

#ifndef BOA_STRINGFUNCTION_H
#define BOA_STRINGFUNCTION_H


#include "../Functions/BaseFunction.h"
#include "../String/String.h"
#include "../List.h"

template<typename T> class StringFunction : public BaseFunction<T> {
public:
    typedef RuntimeResult * (StringFunction<int>::*FnPtr)(Context * execCtx);
    map<string, FnPtr> funcMap;
    vector<BaseValue *> args;
    map<string, BaseValue *> defaultArgs;
    string value;
    StringFunction<T>(string value, string name, vector<string> argNames, map<string, BaseValue *> defaultArgs, string fName, string fTxt);
    RuntimeResult * execute(vector<BaseValue*> args) override;
    StringFunction<int> *copy() override;

    RuntimeResult * execute_split(Context * execCtx);

    string toString() override;
};


#endif //BOA_STRINGFUNCTION_H
