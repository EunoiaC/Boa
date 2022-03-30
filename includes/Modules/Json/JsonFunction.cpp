//
// Created by Preeti Thorat on 3/21/22.
//

#include "JsonFunction.h"

template<>
JsonFunction<int>::JsonFunction(string name, vector<string> argNames, map<string, BaseValue *> defaultArgs,
                                    string fName, string fTxt) : BaseFunction<int>(name, argNames, defaultArgs, fName,
                                                                                   fTxt, CLASS_FUNC) {
    type = "FUNCTION";
    //funcMap["execute_toMap"] = &JsonFunction<int>::execute_toMap;
}

template<>
RuntimeResult *JsonFunction<int>::execute(vector<BaseValue *> args) {
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
JsonFunction<int> *JsonFunction<int>::copy() {
    auto *func = new JsonFunction<int>(name, argNames, defaultArgs, fName, fTxt);
    func->setContext(ctx);
    func->setPos(posStart, posEnd, line);
    return func;
}

template<>
string JsonFunction<int>::toString() {
    return "<JsonFunction: " + name + ">";
}