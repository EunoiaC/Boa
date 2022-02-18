//
// Created by Preeti Thorat on 12/19/21.
//

#include "BaseFunction.h"

#include <utility>
#include "../String/String.h"
#include "../List/List.h"
#include "../Class/Class.h"
#include "../Map.h"

template<> BaseFunction<int>::BaseFunction(string name, vector<string> argNames, map<string, BaseValue *> defaultArgs, string fName, string fTxt, string funcType) : Value<int>(0, T_FUNC, fName, fTxt) {
    this->fName = fName;
    this->fTxt = fTxt;
    this->name = move(name);
    this->argNames = move(argNames);
    this->defaultArgs = move(defaultArgs);
    this->funcType = move(funcType);
}

template<> Context *BaseFunction<int>::generateNewContext() {
    Context *newContext = new Context(name);
    newContext->setParentCtx(ctx);
    newContext->setParentEntry(posStart, fName, fTxt, line);
    newContext->symbolTable = new SymbolTable(newContext->parentCtx->symbolTable);
    return newContext;
}

template<> RuntimeResult *BaseFunction<int>::checkArgs(vector<BaseValue *> args, vector<string> argNames) {
    RuntimeResult *res = new RuntimeResult();
    if (args.size() > argNames.size()) {
        return res->failure(new RuntimeError(
                posStart,
                posEnd,
                args[0]->line,
                fName,
                args[0]->fTxt,
                to_string(args.size() - argNames.size()) + " too many args passed into " + name,
                ctx
        ));
    }

    int normalArgCount = argNames.size() - defaultArgs.size();

    if (args.size() < normalArgCount) {
        return res->failure(new RuntimeError(
                posStart,
                posEnd,
                line,
                fName,
                callTxt,
                to_string(normalArgCount - args.size()) + " too few args passed into " + name,
                ctx
        ));
    }
    return res->success(nullptr);
}

template<> BaseFunction<int> *BaseFunction<int>::copy() {
    BaseFunction<int> * func = new BaseFunction<int>(name, argNames, defaultArgs, fName, fTxt, funcType);
    func->setPos(posStart, posEnd, line);
    func->setContext(ctx);
    return func;
}

template<> void BaseFunction<int>::populateArgs(vector<BaseValue *> args, vector<string> argNames,
                                                Context *context) {
    for (auto &it : defaultArgs) {
        string argName = it.first;
        BaseValue *argValue = it.second;
        if (argValue->type == T_NUM) {
            ((Number<double> *) argValue)->setContext(context);
        } else if (argValue->type == T_STRING) {
            ((String<string> *) argValue)->setContext(context);
        } else if (argValue->type == T_LIST) {
            ((List<vector<BaseValue *>> *) argValue)->setContext(context);
        } if (argValue->type == T_MAP) {
            ((Map<map<BaseValue *, BaseValue *>> *) argValue)->setContext(context);
        }
        context->symbolTable->set(argName, argValue);
    }

    for (int i = 0; i < args.size(); i++) {
        string argName = argNames[i];
        BaseValue *argValue = args[i];
        if (argValue->type == T_NUM) {
            ((Number<double> *) argValue)->setContext(context);
        } else if (argValue->type == T_STRING) {
            ((String<string> *) argValue)->setContext(context);
        } else if (argValue->type == T_LIST) {
            ((List<vector<BaseValue *>> *) argValue)->setContext(context);
        } else if (argValue->type == T_MAP) {
            ((Map<map<BaseValue *, BaseValue *>> *) argValue)->setContext(context);
        } else if (argValue->type == T_CLASS) {
            ((Class<int> *) argValue)->setContext(context);
        }
        context->symbolTable->set(argName, argValue);
    }
}

template<> RuntimeResult *BaseFunction<int>::checkAndPopulateArgs(vector<BaseValue *> args, vector<string> argNames,
                                                                  Context *context) {
    RuntimeResult *res = new RuntimeResult();
    res->reg(checkArgs(args, argNames));
    if(res->shouldReturn()) return res;
    populateArgs(args, argNames, context);
    return res->success(nullptr);
}