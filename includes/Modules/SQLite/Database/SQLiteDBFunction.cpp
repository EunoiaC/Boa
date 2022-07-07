//
// Created by Preeti Thorat on 7/2/22.
//

#include "SQLiteDBFunction.h"

static int callback(void *data, int argc, char **argv, char **azColName){
    SQLiteDB<int> *sqliteObj = (SQLiteDB<int> *) data;
    vector<BaseValue *> asColNameVec;
    vector<BaseValue *> valVec;

    for(int i = 0; i<argc; i++) {
        asColNameVec.push_back(new String<string>(azColName[i], "", ""));
        valVec.push_back(new String<string>(argv[i] ? argv[i] : "NULL", "", ""));
    }

    sqliteObj->callBack->execute({new List<vector<BaseValue *>>(asColNameVec, "", ""), new List<vector<BaseValue *>>(valVec, "", "")}, {});
    return 0;
}

template<>
RuntimeResult *SQLiteDBFunction<int>::execute_setCallback(Context *execCtx) {
    RuntimeResult *res = new RuntimeResult();
    BaseValue * c = execCtx->symbolTable->get("callback");
    if (c->type != TOK_TYPE::T_FUNC) {
        return res->failure(new RuntimeError(
                c->posStart,
                c->posEnd,
                c->line,
                c->fName,
                c->fTxt,
                "Expected a FUNCTION""",
                execCtx
        ));
    }

    Function<int> * func = (Function<int> *) c;
    if (func->argNames.size() != 2) {
        return res->failure(new RuntimeError(
                c->posStart,
                c->posEnd,
                c->line,
                c->fName,
                c->fTxt,
                "Expected a FUNCTION with 2 arguments",
                execCtx
        ));
    }

    sqliteObj->callBack = func;
    return res->success(new Number<double>(0, "", ""));
}

template<>
RuntimeResult *SQLiteDBFunction<int>::execute_exec(Context *execCtx) {
    RuntimeResult *res = new RuntimeResult();
    BaseValue *s = execCtx->symbolTable->get("stmt");
    if (s->type != TOK_TYPE::T_STRING) {
        return res->failure(new RuntimeError(
                s->posStart,
                s->posEnd,
                s->line,
                s->fName,
                s->fTxt,
                "Expected a STRING",
                execCtx
        ));
    }

    if(sqliteObj->callBack == nullptr) {
        return res->failure(new RuntimeError(
                posStart,
                posEnd,
                s->line,
                s->fName,
                s->fTxt,
                "No callback function defined for this SQLiteDB",
                execCtx
        ));
    }

    string stmt = ((String<string> *) s)->val;
    char *zErrMsg = 0;

    int rc = sqlite3_exec(sqliteObj->db, stmt.c_str(), callback, (void*) sqliteObj, &zErrMsg);
    if (rc != SQLITE_OK) {
        return res->failure(new RuntimeError(
                s->posStart,
                s->posEnd,
                s->line,
                s->fName,
                s->fTxt,
                zErrMsg,
                execCtx
        ));
    }

    return res->success(new Number<double>(0, "", ""));
}

template<>
SQLiteDBFunction<int>::SQLiteDBFunction(SQLiteDB<int> *sqliteObj, string name, vector<string> argNames,
                                          map<string, BaseValue *> defaultArgs,
                                          string fName, string fTxt) : BaseFunction<int>(name, argNames, defaultArgs,
                                                                                         fName,
                                                                                         fTxt, CLASS_FUNC) {
    this->sqliteObj = sqliteObj;
    this->defaultArgs = defaultArgs;
    type = TOK_TYPE::T_FUNC;

    funcMap["execute_exec"] = &SQLiteDBFunction<int>::execute_exec;
    funcMap["execute_setCallback"] = &SQLiteDBFunction<int>::execute_setCallback;
}

template<>
SQLiteDBFunction<int> *SQLiteDBFunction<int>::copy() {
    auto *func = new SQLiteDBFunction<int>(sqliteObj, name, argNames, defaultArgs, fName, fTxt);
    func->setContext(ctx);
    func->setPos(posStart, posEnd, line);
    return func;
}

template<>
RuntimeResult *SQLiteDBFunction<int>::execute(vector<BaseValue *> args, map<string, BaseValue *> kwargs) {
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
    res->reg(checkAndPopulateArgs(args, kwargs, argNames, execCtx));
    if (res->error) return res;
    this->args = args;

    BaseValue *returnVal = res->reg((this->*funcMap[methodName])(execCtx));
    if (res->shouldReturn()) return res;

    return res->success(returnVal);
}

template<>
string SQLiteDBFunction<int>::toString() {
    return "<SQLiteDBFunction: " + name + ">";
}