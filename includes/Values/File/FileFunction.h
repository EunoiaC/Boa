//
// Created by Preeti Thorat on 2/27/22.
//

#ifndef BOA_FILEFUNCTION_H
#define BOA_FILEFUNCTION_H


#include "../../Values/Functions/BaseFunction.h"
#include <fstream>
#include <sstream>
#include "../List/List.h"
#include "File.h"

template<typename T> class FileFunction : public BaseFunction<T> {
public:
    typedef RuntimeResult * (FileFunction<int>::*FnPtr)(Context * execCtx);
    map<string, FnPtr> funcMap;
    vector<BaseValue *> args;
    map<string, BaseValue *> defaultArgs;
    File<int> * fileObj;
    FileFunction<T>(File<int> * fileObj, string name, vector<string> argNames, map<string, BaseValue *> defaultArgs, string fName, string fTxt);
    RuntimeResult * execute(vector<BaseValue*> args) override;
    FileFunction<int> *copy() override;

    RuntimeResult * execute_read(Context * execCtx);
    RuntimeResult * execute_readLines(Context * execCtx);
    RuntimeResult * execute_write(Context * execCtx);
    RuntimeResult * execute_writeLines(Context * execCtx);
    RuntimeResult * execute_close(Context * execCtx);

    string toString() override;
};


#endif //BOA_FILEFUNCTION_H
