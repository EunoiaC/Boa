//
// Created by Preeti Thorat on 1/20/22.
//

#include "NumberFunction.h"
#include "math.h"

template<>
RuntimeResult *NumberFunction<int>::execute_ceil(Context *execCtx) {
    return (new RuntimeResult())->success(new Number<double>(ceil(this->value->getValue()), "", ""));
}

template<>
RuntimeResult *NumberFunction<int>::execute_floor(Context *execCtx) {
    return (new RuntimeResult())->success(new Number<double>(floor(this->value->getValue()), "", ""));
}

template<>
NumberFunction<int>::NumberFunction(Number<double>* value, string name, vector<string> argNames, map<string, BaseValue *> defaultArgs, string fName, string fTxt)
        : BaseFunction<int>(name, argNames, defaultArgs, fName, fTxt, CLASS_FUNC) {
    type = TOK_TYPE::T_FUNC; // It doesnt work w/out this idk why
    this->value = value;
    funcMap["execute_ceil"] = &NumberFunction<int>::execute_ceil;
    funcMap["execute_floor"] = &NumberFunction<int>::execute_floor;
    this->defaultArgs = defaultArgs;
}

template<>
RuntimeResult *NumberFunction<int>::execute(vector<BaseValue *> args, map<string, BaseValue *> kwargs) {
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
NumberFunction<int> *NumberFunction<int>::copy() {
    auto *func = new NumberFunction<int>(value, name, argNames, defaultArgs, fName, fTxt);
    func->setContext(ctx);
    func->setPos(posStart, posEnd, line);
    return func;
}

template<>
string NumberFunction<int>::toString() {
    return "<NumberFunction: " + name + ">";
}