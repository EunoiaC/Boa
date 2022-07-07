//
// Created by Preeti Thorat on 4/2/22.
//

#include "FutureFunction.h"
#include <chrono>

template <>
RuntimeResult *FutureFunction<int>::execute_isReady(Context *execCtx) {
    auto * res = new RuntimeResult();
    const auto fs = value->promise.wait_for(chrono::seconds(0));

    if (fs == future_status::deferred) {
        return res->success(new Number<double>(-1, "", ""));
    } else if (fs == future_status::ready) {
        return res->success(new Number<double>(1, "", ""));
    } else if (fs == future_status::timeout) {
        return res->success(new Number<double>(0, "", ""));
    } else {
        return res->success(new Number<double>(-1, "", ""));
    }
}

template <>
RuntimeResult *FutureFunction<int>::execute_get(Context *execCtx) {
    return value->promise.get();
}

template <>
FutureFunction<int>::FutureFunction(Future<shared_future<RuntimeResult *>> * value, string name, vector<string> argNames, map<string, BaseValue *> defaultArgs, string fName, string fTxt)
        : BaseFunction<int>(name, argNames, defaultArgs, fName, fTxt, CLASS_FUNC) {
    type = TOK_TYPE::T_FUNC; // It doesnt work w/out this idk why
    this->value = value;
    funcMap["execute_get"] = &FutureFunction<int>::execute_get;
    funcMap["execute_isReady"] = &FutureFunction<int>::execute_isReady;
    this->defaultArgs = defaultArgs;
}

template<>
RuntimeResult *FutureFunction<int>::execute(vector<BaseValue *> args, map<string, BaseValue *> kwargs) {
    RuntimeResult *res = new RuntimeResult();
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