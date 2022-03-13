//
// Created by Preeti Thorat on 3/12/22.
//

#include "RequestsFunction.h"
#include <curl/curl.h>

template<>
RuntimeResult *RequestsFunction<int>::execute_get(Context *execCtx) {
    BaseValue * url = execCtx->symbolTable->get("url");
    if (url->type != T_STRING){
        return (new RuntimeResult())->failure(new RuntimeError(
                url->posStart,
                url->posEnd,
                url->line,
                url->fName,
                url->fTxt,
                "Expected a STRING",
                execCtx
        ));
    }

    string urlStr = ((String<string> *) url)->getValue();
    

    return RuntimeResult().success(new Number<double>(0, "", ""));
}

template<>
RequestsFunction<int>::RequestsFunction(string name, vector<string> argNames, map<string, BaseValue *> defaultArgs,
                                    string fName, string fTxt) : BaseFunction<int>(name, argNames, defaultArgs, fName,
                                                                                   fTxt, CLASS_FUNC) {
    type = "FUNCTION";
    funcMap["execute_get"] = &RequestsFunction<int>::execute_get;
}

template<>
RuntimeResult *RequestsFunction<int>::execute(vector<BaseValue *> args) {
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
RequestsFunction<int> *RequestsFunction<int>::copy() {
    auto *func = new RequestsFunction<int>(name, argNames, defaultArgs, fName, fTxt);
    func->setContext(ctx);
    func->setPos(posStart, posEnd, line);
    return func;
}

template<>
string RequestsFunction<int>::toString() {
    return "<RequestsFunction: " + name + ">";
}