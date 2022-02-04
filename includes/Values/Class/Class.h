//
// Created by Preeti Thorat on 2/3/22.
//

#ifndef BOA_CLASS_H
#define BOA_CLASS_H

#include "../Number/Number.h"
#include "../Functions/Function.h"
#include "ClassFunction.h"
#include "../../Token/Token.h"

template<typename T> class Class : public Value<T> {
public:
    Context * classContext;
    string name, fName, fTxt;
    vector<Token<string> *> constructorArgs;
    map<string, BaseValue *> defaultArgs;
    vector<ClassFunction<int> *> methods;

    RuntimeResult *execute(vector<BaseValue *> args) override;

    string toString() override;

    BaseValue * copy() override;

    Class<T>(Context * context, string name, string fName, string fTxt, vector<Token<string> *> constructorArgs, map<string, BaseValue *> defaultArgs, vector<ClassFunction<int> *> methods);
};


#endif //BOA_CLASS_H
