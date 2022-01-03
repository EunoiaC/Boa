//
// Created by Preeti Thorat on 12/22/21.
//

#include "BuiltInFunction.h"

template<> RuntimeResult *BuiltInFunction<int>::execute_print(Context *execCtx) {
    cout << execCtx->symbolTable->get("value")->toString() << endl;
    return (new RuntimeResult())->success(new Number<double>(0, fName, fTxt));
}

template<> RuntimeResult *BuiltInFunction<int>::execute_instanceOf(Context *execCtx) {
    return (new RuntimeResult())->success(new String<string>(execCtx->symbolTable->get("value")->type, fName, fTxt));
}

template<> RuntimeResult *BuiltInFunction<int>::execute_toStr(Context *execCtx) {
    string str = execCtx->symbolTable->get("value")->toString();
    return (new RuntimeResult())->success(new String<string>(str, fName, fTxt));
}

template<> RuntimeResult *BuiltInFunction<int>::execute_lenOf(Context *execCtx) {
    BaseValue * val = execCtx->symbolTable->get("value");

    if(val->type == T_NUM){
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

    return (new RuntimeResult())->success(new Number<double>(val->getLength(), fName, fTxt));

}


template<> RuntimeResult *BuiltInFunction<int>::execute_toNum(Context *execCtx) {
    BaseValue * val = execCtx->symbolTable->get("value");
    if(val->type != T_STRING){
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
    String<string> * strVal = (String<string>*) val;
    double v;
    try{
        v = stod(strVal->getValue());
    } catch (invalid_argument e){
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
    return (new RuntimeResult())->success(new Number<double>(v, fName, fTxt));
}

template<> RuntimeResult *BuiltInFunction<int>::execute_input(Context *execCtx) {
    string input;
    BaseValue * val = execCtx->symbolTable->get("value");
    if(val->type != T_STRING){
        return (new RuntimeResult())->failure(
                new RuntimeError(
                        val->posStart,
                        val->posEnd,
                        val->line,
                        val->fName,
                        val->fTxt,
                        "Expected a string",
                        execCtx
                )
                );
    }
    cout << val->toString();
    getline(cin, input);
    String<string> * str = new String<string>(input, val->fName, val->fTxt);
    //cout << str->toString() << endl;
    return (new RuntimeResult())->success(str);
}

template<> BuiltInFunction<int>::BuiltInFunction(string name, vector<string> argNames, string fName, string fTxt) : BaseFunction<int>(name, argNames, fName, fTxt) {
    type = "FUNCTION"; // It doesnt work w/out this idk why

    funcMap["execute_print"] = &BuiltInFunction<int>::execute_print;
    funcMap["execute_input"] = &BuiltInFunction<int>::execute_input;
    funcMap["execute_toNum"] = &BuiltInFunction<int>::execute_toNum;
    funcMap["execute_toStr"] = &BuiltInFunction<int>::execute_toStr;
    funcMap["execute_lenOf"] = &BuiltInFunction<int>::execute_lenOf;
    funcMap["execute_instanceOf"] = &BuiltInFunction<int>::execute_instanceOf;
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