//
// Created by Preeti Thorat on 4/2/22.
//

#include "FutureFunction.h"

template <>
RuntimeResult *FutureFunction<int>::execute_get(Context *execCtx) {
    return value->promise.get();
}

template <>
FutureFunction<int>::FutureFunction(Future<shared_future<RuntimeResult *>> * value, string name, vector<string> argNames, map<string, BaseValue *> defaultArgs, string fName, string fTxt)
        : BaseFunction<int>(name, argNames, defaultArgs, fName, fTxt, CLASS_FUNC) {
    type = "FUNCTION"; // It doesnt work w/out this idk why
    this->value = value;
    funcMap["execute_get"] = &FutureFunction<int>::execute_get;
    this->defaultArgs = defaultArgs;
}

template<>
RuntimeResult *FutureFunction<int>::execute(vector<BaseValue *> args) {
    RuntimeResult *res = new RuntimeResult();
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
FutureFunction<int> *FutureFunction<int>::copy() {
    auto *func = new FutureFunction<int>(value, name, argNames, defaultArgs, fName, fTxt);
    func->setContext(ctx);
    func->setPos(posStart, posEnd, line);
    return func;
}

template<>
string FutureFunction<int>::toString() {
    return "<FutureFunction: " + name + ">";
}