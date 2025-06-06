//
// Created by Preeti Thorat on 1/18/22.
//

#ifndef BOA_LISTFUNCTION_H
#define BOA_LISTFUNCTION_H

#include "../Functions/BaseFunction.h"
#include "../String/String.h"
#include "../List/List.h"
#include "../Map/Map.h"
#include "../Class/UsableClass.h"

template<typename T> class ListFunction : public BaseFunction<T> {
public:
    typedef RuntimeResult * (ListFunction<int>::*FnPtr)(Context * execCtx);
    map<string, FnPtr> funcMap;
    vector<BaseValue *> args;
    map<string, BaseValue *> defaultArgs;
    List<vector<BaseValue*>>* value;
    ListFunction<T>(List<vector<BaseValue*>>* value, string name, vector<string> argNames, map<string, BaseValue *> defaultArgs, string fName, string fTxt);
    RuntimeResult * execute(vector<BaseValue*> args, map<string, BaseValue *> kwargs) override;
    ListFunction<int> *copy() override;

    RuntimeResult * execute_pop(Context * execCtx);
    RuntimeResult * execute_append(Context * execCtx);
    RuntimeResult * execute_slice(Context * execCtx);
    RuntimeResult * execute_indexOf(Context * execCtx);
    RuntimeResult * execute_set(Context * execCtx);
    RuntimeResult * execute_sort(Context * execCtx);

    string toString() override;
};


#endif //BOA_LISTFUNCTION_H
