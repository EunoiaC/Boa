//
// Created by Preeti Thorat on 6/22/22.
//

#include "GUIFunction.h"

template<>
RuntimeResult *GUIFunction<int>::execute_makeWindow(Context *execCtx) {
    BaseValue * w = execCtx->symbolTable->get("width");
    if (w->type != TOK_TYPE::T_NUM) {
        return (new RuntimeResult())->failure(new RuntimeError(
                w->posStart,
                w->posEnd,
                w->line,
                w->fName,
                w->fTxt,
                "Expected a STRING",
                execCtx
        ));
    }

    BaseValue * h = execCtx->symbolTable->get("width");
    if (h->type != TOK_TYPE::T_NUM) {
        return (new RuntimeResult())->failure(new RuntimeError(
                h->posStart,
                h->posEnd,
                h->line,
                h->fName,
                h->fTxt,
                "Expected a STRING",
                execCtx
        ));
    }

    BaseValue * t = execCtx->symbolTable->get("title");
    if (t->type != TOK_TYPE::T_STRING) {
        return (new RuntimeResult())->failure(new RuntimeError(
                t->posStart,
                t->posEnd,
                t->line,
                t->fName,
                t->fTxt,
                "Expected a STRING",
                execCtx
        ));
    }

    Number<double> * width = (Number<double> *) w;
    Number<double> * height = (Number<double> *) h;
    String<string> * title = (String<string> *) t;

    return (new RuntimeResult())->success(new Window<int>(width, height, title));
}

template<>
GUIFunction<int>::GUIFunction(string name, vector<string> argNames,
                                    map<string, BaseValue *> defaultArgs,
                                    string fName, string fTxt) : BaseFunction<int>(name, argNames, defaultArgs,
                                                                                   fName,
                                                                                   fTxt, CLASS_FUNC) {
    this->defaultArgs = defaultArgs;
    type = TOK_TYPE::T_FUNC;

    funcMap["execute_makeWindow"] = &GUIFunction<int>::execute_makeWindow;
}

template<>
GUIFunction<int> *GUIFunction<int>::copy() {
    auto *func = new GUIFunction<int>(name, argNames, defaultArgs, fName, fTxt);
    func->setContext(ctx);
    func->setPos(posStart, posEnd, line);
    return func;
}

template<>
RuntimeResult *GUIFunction<int>::execute(vector<BaseValue *> args) {
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
string GUIFunction<int>::toString() {
    return "<GUIFunction: " + name + ">";
}