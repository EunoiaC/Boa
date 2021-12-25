//
// Created by Preeti Thorat on 12/19/21.
//

#include "BaseFunction.h"

template<> BaseFunction<int>::BaseFunction(string name, vector<string> argNames, string fName, string fTxt) : Value<int>(0, T_FUNC, fName, fTxt) {
    this->fName = fName;
    this->fTxt = fTxt;
    this->name = name;
    this->argNames = argNames;
    symbolTable->set("type", new String<string>("FUNCTION", "", ""));
}

template<> Context *BaseFunction<int>::generateNewContext() {
    Context *newContext = new Context(name);
    newContext->setParentEntry(posStart, fName, fTxt, line);
    newContext->setParentCtx(ctx);
    newContext->symbolTable = (new SymbolTable())->setParent(newContext->parentCtx->symbolTable);
    return newContext;
}

template<> RuntimeResult *BaseFunction<int>::checkArgs(vector<BaseValue *> args, vector<string> argNames) {
    RuntimeResult *res = new RuntimeResult();
    if (args.size() > argNames.size()) {
        return res->failure(new RuntimeError(
                posStart,
                posEnd,
                line,
                fName,
                callTxt,
                to_string(args.size() - argNames.size()) + " too many args passed into " + name,
                ctx
        ));
    }

    if (args.size() < argNames.size()) {
        return res->failure(new RuntimeError(
                posStart,
                posEnd,
                line,
                fName,
                callTxt,
                to_string(argNames.size() - args.size()) + " too few args passed into " + name,
                ctx
        ));
    }
    return res->success(nullptr);
}

template<> BaseFunction<int> *BaseFunction<int>::copy() {
    BaseFunction<int> * func = new BaseFunction<int>(name, argNames, fName, fTxt);
    func->setPos(posStart, posEnd, line);
    func->setContext(ctx);
    return func;
}

template<> void BaseFunction<int>::populateArgs(vector<BaseValue *> args, vector<string> argNames,
                                                Context *context) {
    for (int i = 0; i < args.size(); i++) {
        string argName = argNames[i];
        BaseValue *argValue = args[i];
        if (argValue->type == T_NUM) {
            ((Number<double> *) argValue)->setContext(context);
        }
        context->symbolTable->set(argName, argValue);
    }
}

template<> RuntimeResult *BaseFunction<int>::checkAndPopulateArgs(vector<BaseValue *> args, vector<string> argNames,
                                                                  Context *context) {
    RuntimeResult *res = new RuntimeResult();
    res->reg(checkArgs(args, argNames));
    if(res->error) return res;
    populateArgs(args, argNames, context);
    return res->success(nullptr);
}