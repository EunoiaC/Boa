//
// Created by Preeti Thorat on 2/27/22.
//

#include "FileFunction.h"

template<>
RuntimeResult *FileFunction<int>::execute_readLines(Context *execCtx) {
    fileObj->file.clear();
    fileObj->file.seekg(0);

    vector<BaseValue *> lines;
    string str;
    // Read the next line from File until it reaches the end.
    while (getline(fileObj->file, str)) {
        lines.push_back(new String<string>(str, "", ""));
    }
    return (new RuntimeResult())->success(new List<vector<BaseValue *>>(lines, "", ""));
}

template<>
RuntimeResult *FileFunction<int>::execute_read(Context *execCtx) {
    fileObj->file.clear();
    fileObj->file.seekg(0);

    stringstream buffer;
    buffer << fileObj->file.rdbuf();
    string fileText = buffer.str();
    return (new RuntimeResult())->success(new String<string>(fileText, "", ""));
}

template<>
RuntimeResult *FileFunction<int>::execute_write(Context *execCtx) {
    fstream temp = fstream(fileObj->parentPath->getValue() + fileObj->fileName->getValue(), ios::app);

    BaseValue *toAdd = execCtx->symbolTable->get("toAdd");
    temp << toAdd->toString();

    temp.close();

    return (new RuntimeResult())->success(new Number<double>(0, "", ""));
}

template<>
RuntimeResult *FileFunction<int>::execute_writeLines(Context *execCtx) {
    auto * res = new RuntimeResult();
    BaseValue * l = execCtx->symbolTable->get("list");
    if (l->type != TOK_TYPE::T_LIST) {
        return res->failure(new RuntimeError(
                l->posStart,
                l->posEnd,
                l->line,
                l->fName,
                l->fTxt,
                "Expected a LIST",
                execCtx
        ));
    }

    List<vector<BaseValue *>> * list = dynamic_cast<List<vector<BaseValue *>> *>(l);
    ofstream temp = ofstream(fileObj->parentPath->getValue() + fileObj->fileName->getValue(), ios::out | ios::trunc);
    temp.close();

    fstream toWrite = fstream(fileObj->parentPath->getValue() + fileObj->fileName->getValue(), ios::app);
    for (auto &i : list->elements) {
        toWrite << i->toString() << endl;
    }

    return res->success(new Number<double>(0, "", ""));
}

template<>
RuntimeResult *FileFunction<int>::execute_close(Context *execCtx) {
    fileObj->file.close();
    return (new RuntimeResult())->success(new Number<double>(0, "", ""));
}

template<>
FileFunction<int>::FileFunction(File<int> *fileObj, string name, vector<string> argNames,
                                map<string, BaseValue *> defaultArgs,
                                string fName, string fTxt) : BaseFunction<int>(name, argNames, defaultArgs, fName,
                                                                               fTxt, CLASS_FUNC) {
    this->fileObj = fileObj;
    type = TOK_TYPE::T_FUNC;
    funcMap["execute_readLines"] = &FileFunction<int>::execute_readLines;
    funcMap["execute_read"] = &FileFunction<int>::execute_read;
    funcMap["execute_write"] = &FileFunction<int>::execute_write;
    funcMap["execute_writeLines"] = &FileFunction<int>::execute_writeLines;
    funcMap["execute_close"] = &FileFunction<int>::execute_close;
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