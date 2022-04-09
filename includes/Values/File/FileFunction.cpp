//
// Created by Preeti Thorat on 2/27/22.
//

#include "FileFunction.h"

template<>
RuntimeResult *FileFunction<int>::execute_readLines(Context *execCtx) {
    String<string> *fileName = fileObj->fileName;
    ifstream file(fileName->getValue());
    if (file.fail()) {
        file = ifstream(ctx->parentFilePath + fileName->getValue());
    }
    if (file.fail()) {
        return (new RuntimeResult())->failure(
                new RuntimeError(
                        fileName->posStart,
                        fileName->posEnd,
                        fileName->line,
                        fileName->fName,
                        fileName->fTxt,
                        "File doesn't exist",
                        execCtx
                )
        );
    }
    vector<BaseValue *> lines;
    string str;
    // Read the next line from File until it reaches the end.
    while (getline(file, str)) {
        // Line contains string of length > 0 then save it in vector
        if (str.size() > 0)
            lines.push_back(new String<string>(str, "", ""));
    }
    //Close The File
    file.close();

    return (new RuntimeResult())->success(new List<vector<BaseValue *>>(lines, "", ""));
}

template<>
RuntimeResult *FileFunction<int>::execute_read(Context *execCtx) {
    String<string> *fileName = fileObj->fileName;
    ifstream file(fileName->getValue());
    if (file.fail()) {
        file = ifstream(ctx->parentFilePath + fileName->getValue());
    }
    if (file.fail()) {
        return (new RuntimeResult())->failure(
                new RuntimeError(
                        fileName->posStart,
                        fileName->posEnd,
                        fileName->line,
                        fileName->fName,
                        fileName->fTxt,
                        "File doesn't exist",
                        execCtx
                )
        );
    }
    stringstream buffer;
    buffer << file.rdbuf();
    string fileText = buffer.str();
    return (new RuntimeResult())->success(new String<string>(fileText, "", ""));
}

template<>
FileFunction<int>::FileFunction(File<int> *fileObj, string name, vector<string> argNames,
                                map<string, BaseValue *> defaultArgs,
                                string fName, string fTxt) : BaseFunction<int>(name, argNames, defaultArgs, fName,
                                                                               fTxt, CLASS_FUNC) {
    this->fileObj = fileObj;
    type = "FUNCTION";
    funcMap["execute_readLines"] = &FileFunction<int>::execute_readLines;
    funcMap["execute_read"] = &FileFunction<int>::execute_read;
}

template<>
FileFunction<int> *FileFunction<int>::copy() {
    auto *func = new FileFunction<int>(fileObj, name, argNames, defaultArgs, fName, fTxt);
    func->setContext(ctx);
    func->setPos(posStart, posEnd, line);
    return func;
}

template<>
RuntimeResult *FileFunction<int>::execute(vector<BaseValue *> args) {
    auto *res = new RuntimeResult();
    Context *execCtx = generateNewContext();

    string methodName = "execute_" + name;

    res->reg(checkAndPopulateArgs(args, argNames, execCtx));
    if (res->error) return res;
    this->args = args;

    BaseValue *returnVal = res->reg((this->*funcMap[methodName])(execCtx));
    if (res->shouldReturn()) return res;

    return res->success(returnVal);
}

template<>
string FileFunction<int>::toString() {
    return "<FileFunction: " + name + ">";
}