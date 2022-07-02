//
// Created by Preeti Thorat on 7/2/22.
//

#ifndef BOA_SQLITEDBFUNCTION_H
#define BOA_SQLITEDBFUNCTION_H


#include "../../Values/Functions/BaseFunction.h"
#include <fstream>
#include "../../Values/List/List.h"
#include "../../Values/Functions/Function.h"
#include <sqlite3.h>
#include "Database/SQLiteDB.h"

template<typename T> class SQLite3Function : public BaseFunction<T> {
public:
    typedef RuntimeResult * (SQLite3Function<int>::*FnPtr)(Context * execCtx);
    map<string, FnPtr> funcMap;
    vector<BaseValue *> args;
    map<string, BaseValue *> defaultArgs;
    SQLite3Function<T>(string name, vector<string> argNames, map<string, BaseValue *> defaultArgs, string fName, string fTxt);
    RuntimeResult * execute(vector<BaseValue*> args, map<string, BaseValue *> kwargs) override;
    SQLite3Function<int> *copy() override;

    RuntimeResult * execute_open(Context * execCtx);

    string toString() override;
};


#endif //BOA_SQLITEDBFUNCTION_H
