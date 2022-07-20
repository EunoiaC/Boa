//
// Created by Preeti Thorat on 7/18/22.
//

#include "TextFunction.h"

template<>
RuntimeResult *TextFunction<int>::execute_setText(Context *execCtx) {
    RuntimeResult * res = new RuntimeResult();
    BaseValue * s = execCtx->symbolTable->get("text");
    if (s->type != TOK_TYPE::T_STRING) {
        return (new RuntimeResult())->failure(new RuntimeError(
                s->posStart,
                s->posEnd,
                s->line,
                s->fName,
                s->fTxt,
                "Expected a STRING",
                execCtx
        ));
    }
    String<string> * str = (String<string> *) s;
    txtObj->buffer.text(str->val.c_str());
    return res->success(new Number<double>(0, "", ""));
}

template<>
TextFunction<int>::TextFunction(Text<int> *txtObj, string name, vector<string> argNames,
                                          map<string, BaseValue *> defaultArgs,
                                          string fName, string fTxt) : BaseFunction<int>(name, argNames, defaultArgs,
                                                                                         fName,
                                                                                         fTxt, CLASS_FUNC) {
    this->txtObj = txtObj;
    this->defaultArgs = defaultArgs;
    type = TOK_TYPE::T_FUNC;

    funcMap["execute_setText"] = &TextFunction<int>::execute_setText;
}

template<>
TextFunction<int> *TextFunction<int>::copy() {
    auto *func = new TextFunction<int>(txtObj, name, argNames, defaultArgs, fName, fTxt);
    func->setContext(ctx);
    func->setPos(posStart, posEnd, line);
    return func;
}

template<>
RuntimeResult *TextFunction<int>::execute(vector<BaseValue *> args, map<string, BaseValue *> kwargs) {
    auto *res = new RuntimeResult();
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
string TextFunction<int>::toString() {
    return "<TextFunction: " + name + ">";
}