//
// Created by Preeti Thorat on 7/2/22.
//

#include "SQLite3Function.h"

template<>
RuntimeResult *SQLite3Function<int>::execute_open(Context *execCtx) {
    RuntimeResult *res = new RuntimeResult();
    BaseValue * d = execCtx->symbolTable->get("db");
    if (d->type != TOK_TYPE::T_STRING) {
        return (new RuntimeResult())->failure(new RuntimeError(
                d->posStart,
                d->posEnd,
                d->line,
                d->fName,
                d->fTxt,
                "Expected a STRING",
                execCtx
        ));
    }

    string dbName = ((String<string> *)d)->val;
    sqlite3 *db;
    int rc = sqlite3_open((execCtx->parentFilePath + dbName).c_str(), &db);
    if (rc) {
        rc = sqlite3_open(dbName.c_str(), &db);
        if (rc) {
            return (new RuntimeResult())->failure(new RuntimeError(
                    d->posStart,
                    d->posEnd,
                    d->line,
                    d->fName,
                    d->fTxt,
                    "Could not open database",
                    execCtx
            ));
        }
    }

    return res->success(new SQLiteDB<int>(db));
}

template<>
SQLite3Function<int>::SQLite3Function(string name, vector<string> argNames,
                                          map<string, BaseValue *> defaultArgs,
                                          string fName, string fTxt) : BaseFunction<int>(name, argNames, defaultArgs,
                                                                                         fName,
                                                                                         fTxt, CLASS_FUNC) {
    this->defaultArgs = defaultArgs;
    type = TOK_TYPE::T_FUNC;
    funcMap["execute_open"] = &SQLite3Function<int>::execute_open;
}

template<>
SQLite3Function<int> *SQLite3Function<int>::copy() {
    auto *func = new SQLite3Function<int>(name, argNames, defaultArgs, fName, fTxt);
    func->setContext(ctx);
    func->setPos(posStart, posEnd, line);
    return func;
}

template<>
RuntimeResult *SQLite3Function<int>::execute(vector<BaseValue *> args, map<string, BaseValue *> kwargs) {
    auto *res = new RuntimeResult();
    Context *execCtx = generateNewContext();

    string methodName = "execute_" + name;

    for (auto &it: kwargs) {
        // Check if the keyword argument is a valid argument
        if (find(argNames.begin(), argNames.end(), it.first) == argNames.end()) {
            return res->failure(new RuntimeError(
                    posStart,
                    posEnd,
                    line,
                    fName,
                    fTxt,
                    "Invalid keyword argument " + it.first + " passed into " + name,
                    ctx
            ));
        }
        args.push_back(it.second);
        execCtx->symbolTable->set(it.first, it.second);
    }
    res->reg(checkAndPopulateArgs(args, argNames, execCtx));
    if (res->error) return res;
    this->args = args;

    BaseValue *returnVal = res->reg((this->*funcMap[methodName])(execCtx));
    if (res->shouldReturn()) return res;

    return res->success(returnVal);
}

template<>
string SQLite3Function<int>::toString() {
    return "<SQLite3Function: " + name + ">";
}