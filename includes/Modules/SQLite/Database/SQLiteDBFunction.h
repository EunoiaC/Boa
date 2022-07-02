//
// Created by Preeti Thorat on 7/2/22.
//

#ifndef BOA_SQLITEDBFUNCTION_H
#define BOA_SQLITEDBFUNCTION_H


#include "../../../Values/Functions/BaseFunction.h"
#include <fstream>
#include "../../../Values/List/List.h"
#include "../../../Values/Functions/Function.h"
#include "SQLiteDB.h"

template<typename T> class SQLiteDBFunction : public BaseFunction<T> {
public:
    typedef RuntimeResult * (SQLiteDBFunction<int>::*FnPtr)(Context * execCtx);
    map<string, FnPtr> funcMap;
    vector<BaseValue *> args;
    map<string, BaseValue *> defaultArgs;
    SQLiteDB<int> * sqliteObj;
    SQLiteDBFunction<T>(SQLiteDB<int> * sqliteObj, string name, vector<string> argNames, map<string, BaseValue *> defaultArgs, string fName, string fTxt);
    RuntimeResult * execute(vector<BaseValue*> args, map<string, BaseValue *> kwargs) override;
    SQLiteDBFunction<int> *copy() override;

    RuntimeResult * execute_exec(Context * execCtx);
    RuntimeResult * execute_setCallback(Context * execCtx);

    string toString() override;
};


#endif //BOA_SQLITEDBFUNCTION_H
