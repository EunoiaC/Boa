//
// Created by Preeti Thorat on 12/19/21.
//

#ifndef BOA_BASEFUNCTION_H
#define BOA_BASEFUNCTION_H

#include "../Number.h"

template<typename T> class BaseFunction : public Value<T> {
public:
    string name, callTxt;
    vector<string> argNames;
    vector<string> lines;
    BaseFunction<T>(string name, vector<string> argNames, vector<string> lines, string fName, string fTxt);
    Context * generateNewContext();
    RuntimeResult * checkArgs(vector<BaseValue *> args, vector<string> argNames);
    void populateArgs(vector<BaseValue *> args, vector<string> argNames, Context * context);
    RuntimeResult * checkAndPopulateArgs(vector<BaseValue *> args, vector<string> argNames, Context * context);
};


#endif //BOA_BASEFUNCTION_H