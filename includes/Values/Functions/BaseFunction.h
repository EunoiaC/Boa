//
// Created by Preeti Thorat on 12/19/21.
//

#ifndef BOA_BASEFUNCTION_H
#define BOA_BASEFUNCTION_H

#include "../Number/Number.h"

static const string BUILT_IN_FUNC = "BUILT_IN_FUNCTION";
static const string NORMAL_FUNC = "NORMAL_FUNCTION";
static const string CLASS_FUNC = "CLASS_FUNCTION";

template<typename T> class BaseFunction : public Value<T> {
public:
    string name, callTxt, funcType;
    vector<string> argNames;
    map<string, BaseValue *> defaultArgs;
    BaseFunction<T>(string name, vector<string> argNames, map<string, BaseValue *> defaultArgs, string fName, string fTxt, string funcType);
    BaseFunction<T> * copy() override;
    Context * generateNewContext();
    RuntimeResult * checkArgs(vector<BaseValue *> args, vector<string> argNames);
    void populateArgs(vector<BaseValue *> args, vector<string> argNames, Context * context);
    RuntimeResult * checkAndPopulateArgs(vector<BaseValue *> args, vector<string> argNames, Context * context);
};


#endif //BOA_BASEFUNCTION_H