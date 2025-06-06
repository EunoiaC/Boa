//
// Created by Preeti Thorat on 12/22/21.
//

#include "BuiltInFunction.h"
#include "../../RunInterface.h"


template<>
RuntimeResult *BuiltInFunction<int>::execute_print(Context *execCtx) {
    string output;
    for (auto &arg: args) {
        output += arg->toString() + " ";
    }
    cout << output << endl;
    return (new RuntimeResult())->success(new Number<double>(0, fName, fTxt));
}

template<>
RuntimeResult *BuiltInFunction<int>::execute_instanceOf(Context *execCtx) {
    auto *res = new RuntimeResult();
    res->reg(checkArgs(args, argNames, kwargs));
    if (res->error) return res;

    BaseValue *val = execCtx->symbolTable->get("value");

    if (val->type == TOK_TYPE::T_CLASS) {
        auto *classVal = dynamic_cast<UsableClass<int> *>(val);
        if (classVal) {
            return (new RuntimeResult())->success(new String<string>(classVal->className, val->fName, val->fTxt));
        }
        return (new RuntimeResult())->success(new String<string>(((Class<int> *)val)->name, val->fName, val->fTxt));
    }

    return (new RuntimeResult())->success(new String<string>(VAL_TYPES[val->type], val->fName, val->fTxt));
}

template<>
RuntimeResult *BuiltInFunction<int>::execute_toStr(Context *execCtx) {
    auto *res = new RuntimeResult();
    res->reg(checkArgs(args, argNames, kwargs));
    if (res->error) return res;

    BaseValue *str = execCtx->symbolTable->get("value");
    string toStr = str->toString();
    return (new RuntimeResult())->success(new String<string>(toStr, str->fName, str->fTxt));
}

template<>
RuntimeResult *BuiltInFunction<int>::execute_lenOf(Context *execCtx) {
    auto *res = new RuntimeResult();
    res->reg(checkArgs(args, argNames, kwargs));
    if (res->error) return res;

    BaseValue *val = execCtx->symbolTable->get("value");

    if (val->type == TOK_TYPE::T_NUM) {
        return (new RuntimeResult())->failure(
                new RuntimeError(
                        val->posStart,
                        val->posEnd,
                        val->line,
                        val->fName,
                        val->fTxt,
                        "Can't get length of type NUMBER",
                        execCtx
                )
        );
    }

    return (new RuntimeResult())->success(new Number<double>(val->getLength(), val->fName, val->fTxt));

}


template<>
RuntimeResult *BuiltInFunction<int>::execute_toNum(Context *execCtx) {
    auto *res = new RuntimeResult();
    res->reg(checkArgs(args, argNames, kwargs));
    if (res->error) return res;

    BaseValue *val = execCtx->symbolTable->get("value");
    if (val->type != TOK_TYPE::T_STRING) {
        return (new RuntimeResult())->failure(
                new RuntimeError(
                        val->posStart,
                        val->posEnd,
                        val->line,
                        val->fName,
                        val->fTxt,
                        "Expected a STRING",
                        execCtx
                )
        );
    }
    auto *strVal = (String<string> *) val;
    double v;
    try {
        v = stod(strVal->getValue());
    } catch (invalid_argument e) {
        return (new RuntimeResult())->failure(
                new RuntimeError(
                        val->posStart,
                        val->posEnd,
                        val->line,
                        val->fName,
                        val->fTxt,
                        "String has characters that can't be converted to type NUMBER",
                        execCtx
                )
        );
    }
    return (new RuntimeResult())->success(new Number<double>(v, strVal->fName, strVal->fTxt));
}

template<>
RuntimeResult *BuiltInFunction<int>::execute_input(Context *execCtx) {
    string output;
    string ftxt = "keyboard input\n";
    for (auto &arg: args) {
        output += arg->toString() + " ";
        ftxt = arg->fTxt;
    }

    string input;
    cout << output;
    getline(cin, input);
    auto *str = new String<string>(input, "", ftxt);
    //cout << str->toString() << endl;
    return (new RuntimeResult())->success(str);
}

template<>
RuntimeResult *BuiltInFunction<int>::execute_eval(Context *execCtx) {
    auto *res = new RuntimeResult();
    res->reg(checkArgs(args, argNames, kwargs));
    if (res->error) return res;

    BaseValue *val = execCtx->symbolTable->get("value");
    if (val->type != TOK_TYPE::T_STRING) {
        return (new RuntimeResult())->failure(
                new RuntimeError(
                        val->posStart,
                        val->posEnd,
                        val->line,
                        val->fName,
                        val->fTxt,
                        "Expected a STRING",
                        execCtx
                )
        );
    }

    SymbolTable *symToUse = execCtx->symbolTable;

    while (symToUse->parent) {
        symToUse = symToUse->parent;
    }

    auto *runInterface = new RunInterface(symToUse, "");
    RunResult r = runInterface->readLine(((String<string> *) val)->getValue());
    if (r.second) {
        cout << r.second->toString() << endl;
        return (new RuntimeResult())->success(new Number<double>(-1, "", ""));
    }
    return (new RuntimeResult())->success(r.first);
}

template<>
RuntimeResult *BuiltInFunction<int>::execute_rename(Context *execCtx) {
    auto *res = new RuntimeResult();
    res->reg(checkArgs(args, argNames, kwargs));
    if (res->error) return res;

    BaseValue *oldName = execCtx->symbolTable->get("oldName");
    if (oldName->type != TOK_TYPE::T_STRING) {
        return (new RuntimeResult())->failure(
                new RuntimeError(
                        oldName->posStart,
                        oldName->posEnd,
                        oldName->line,
                        oldName->fName,
                        oldName->fTxt,
                        "Expected a STRING",
                        execCtx
                )
        );
    }

    BaseValue *newName = execCtx->symbolTable->get("newName");
    if (newName->type != TOK_TYPE::T_STRING) {
        return (new RuntimeResult())->failure(
                new RuntimeError(
                        newName->posStart,
                        newName->posEnd,
                        newName->line,
                        newName->fName,
                        newName->fTxt,
                        "Expected a STRING",
                        execCtx
                )
        );
    }

    BaseValue *valToTransfer = execCtx->symbolTable->get(oldName->toString());

    if (valToTransfer == nullptr) {
        return (new RuntimeResult())->failure(
                new RuntimeError(
                        oldName->posStart,
                        oldName->posEnd,
                        oldName->line,
                        oldName->fName,
                        oldName->fTxt,
                        "Variable doesn't exist",
                        execCtx
                )
        );
    }

    SymbolTable *mainSym = execCtx->symbolTable;

    while (mainSym->parent) {
        mainSym = mainSym->parent;
    }

    mainSym->set(newName->toString(), valToTransfer->copy());
    mainSym->remove(oldName->toString());

    return (new RuntimeResult())->success(new Number<double>(0, "", ""));
}

template<>
RuntimeResult *BuiltInFunction<int>::execute_getSymbolTable(Context *execCtx) {
    auto *res = new RuntimeResult();
    res->reg(checkArgs(args, argNames, kwargs));
    if (res->error) return res;

    auto *sym = new Map<map<BaseValue *, BaseValue *>>({}, "", "");

    SymbolTable *mainSym = execCtx->symbolTable;
    while (mainSym->parent) {
        mainSym = mainSym->parent;
    }

    for (auto &it: mainSym->symbols) {
        auto *key = new String<string>(it.first, "", "");
        BaseValue *val = it.second->copy();

        sym->plusEquals(new List<vector<BaseValue *>>({key, val}, "", ""));
    }


    return (new RuntimeResult())->success(sym);
}

template<>
RuntimeResult *BuiltInFunction<int>::execute_copy(Context *execCtx) {
    auto *res = new RuntimeResult();
    res->reg(checkArgs(args, argNames, kwargs));
    if (res->error) return res;

    return (new RuntimeResult())->success(execCtx->symbolTable->get("value")->copy());
}

template<>
RuntimeResult *BuiltInFunction<int>::execute_getFile(Context *execCtx) {
    auto *res = new RuntimeResult();
    res->reg(checkArgs(args, argNames, kwargs));
    if (res->error) return res;

    BaseValue *f = execCtx->symbolTable->get("fName");
    if (f->type != TOK_TYPE::T_STRING) {
        return (new RuntimeResult())->failure(
                new RuntimeError(
                        f->posStart,
                        f->posEnd,
                        f->line,
                        f->fName,
                        f->fTxt,
                        "Expected a STRING",
                        execCtx
                )
        );
    }

    auto *fName = (String<string> *) f;

    auto *fileObj = new File<int>(fName, new String<string>(ctx->parentFilePath, "", ""));

    return (new RuntimeResult())->success(fileObj);
}

template<>
RuntimeResult *BuiltInFunction<int>::execute_clear(Context *execCtx) {
    auto *res = new RuntimeResult();
    res->reg(checkArgs(args, argNames, kwargs));
    if (res->error) return res;

    system("clear");
    return (new RuntimeResult())->success(new Number<double>(0, "", ""));
}

template<>
BuiltInFunction<int>::BuiltInFunction(string name, vector<string> argNames, map<string, BaseValue *> defaultArgs,
                                      string fName, string fTxt)
        : BaseFunction<int>(name, argNames, defaultArgs, fName, fTxt, BUILT_IN_FUNC) {
    type = TOK_TYPE::T_FUNC; // It doesnt work w/out this idk why

    funcMap["execute_print"] = &BuiltInFunction<int>::execute_print;
    funcMap["execute_input"] = &BuiltInFunction<int>::execute_input;
    funcMap["execute_toNum"] = &BuiltInFunction<int>::execute_toNum;
    funcMap["execute_toStr"] = &BuiltInFunction<int>::execute_toStr;
    funcMap["execute_lenOf"] = &BuiltInFunction<int>::execute_lenOf;
    funcMap["execute_instanceOf"] = &BuiltInFunction<int>::execute_instanceOf;
    funcMap["execute_copy"] = &BuiltInFunction<int>::execute_copy;
    funcMap["execute_eval"] = &BuiltInFunction<int>::execute_eval;
    funcMap["execute_rename"] = &BuiltInFunction<int>::execute_rename;
    funcMap["execute_getFile"] = &BuiltInFunction<int>::execute_getFile;
    funcMap["execute_getSymbolTable"] = &BuiltInFunction<int>::execute_getSymbolTable;
    funcMap["execute_clear"] = &BuiltInFunction<int>::execute_clear;
}

template<>
RuntimeResult *BuiltInFunction<int>::execute(vector<BaseValue *> args, map<string, BaseValue *> kwargs) {
    RuntimeResult *res = new RuntimeResult();
    Context *execCtx = generateNewContext();

    string methodName = "execute_" + name;

    populateArgs(args, argNames, kwargs, execCtx);
    this->args = args;
    this->kwargs = kwargs;

    BaseValue *returnVal = res->reg((this->*funcMap[methodName])(execCtx));
    if (res->shouldReturn()) return res;

    return res->success(returnVal);
}

template<>
BuiltInFunction<int> *BuiltInFunction<int>::copy() {
    BuiltInFunction<int> *func = new BuiltInFunction<int>(name, argNames, defaultArgs, fName, fTxt);
    func->setContext(ctx);
    func->setPos(posStart, posEnd, line);
    return func;
}

template<>
string BuiltInFunction<int>::toString() {
    return "<BuiltinFunction: " + name + ">";
}