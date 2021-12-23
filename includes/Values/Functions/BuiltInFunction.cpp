//
// Created by Preeti Thorat on 12/22/21.
//

#include "BuiltInFunction.h"

template<> RuntimeResult *BuiltInFunction<int>::execute_print(Context *execCtx) {
    cout << execCtx->symbolTable->get("value")->toString() << endl;
    return (new RuntimeResult())->success(new Number<double>(0, fName, fTxt));
}

template<> BuiltInFunction<int>::BuiltInFunction(string name, vector<string> argNames, string fName, string fTxt) : BaseFunction<int>(name, argNames, fName, fTxt) {
    type = "FUNCTION"; // It doesnt work w/out this idk why

    funcMap["execute_print"] = &BuiltInFunction<int>::execute_print;
}

template<> RuntimeResult *BuiltInFunction<int>::execute(vector<BaseValue*> args) {
    RuntimeResult * res = new RuntimeResult();
    Context * execCtx = generateNewContext();

    string methodName = "execute_" + name;

    res->reg(checkAndPopulateArgs(args, argNames, execCtx));
    if(res->error) return res;

    BaseValue * returnVal = res->reg((this->*funcMap[methodName])(execCtx));
    if(res->error) return res;

    return res->success(returnVal);
}

template<> BuiltInFunction<int> *BuiltInFunction<int>::copy() {
    BuiltInFunction<int> * func = new BuiltInFunction<int>(name, argNames, fName, fTxt);
    func->setContext(ctx);
    func->setPos(posStart, posEnd, line);
    return func;
}

template<> string BuiltInFunction<int>::toString() {
    return "<BuiltinFunction: " + name + ">";
}