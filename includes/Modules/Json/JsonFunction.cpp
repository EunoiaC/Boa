//
// Created by Preeti Thorat on 3/21/22.
//

#include "JsonFunction.h"
#include "nlohmann/json.hpp"

template<> RuntimeResult *JsonFunction<int>::execute_toMap(Context *execCtx) {
    auto * res = new RuntimeResult();

    BaseValue * temp = execCtx->symbolTable->get("string");
    if (temp->type != T_STRING){
        res->failure(new RuntimeError(
                temp->posStart,
                temp->posEnd,
                temp->line,
                temp->fName,
                temp->fTxt,
                "Expected a STRING",
                execCtx
        ));
    }

    String<string> * jsonStr = (String<string> *) temp;
    auto parsedObj = nlohmann::json ::parse(jsonStr->getValue());

    for(nlohmann::json::iterator it = parsedObj.begin(); it != parsedObj.end(); ++it) {
        cout << it.key();
        cout << it.value();
    }
}

template<>
JsonFunction<int>::JsonFunction(string name, vector<string> argNames, map<string, BaseValue *> defaultArgs,
                                    string fName, string fTxt) : BaseFunction<int>(name, argNames, defaultArgs, fName,
                                                                                   fTxt, CLASS_FUNC) {
    type = "FUNCTION";
    funcMap["execute_toMap"] = &JsonFunction<int>::execute_toMap;
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