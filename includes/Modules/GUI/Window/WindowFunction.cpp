//
// Created by Preeti Thorat on 6/21/22.
//

#include "WindowFunction.h"

template<>
RuntimeResult *WindowFunction<int>::execute_start(Context *execCtx) {
    while(!glfwWindowShouldClose(winObj->window)) {
        glfwSwapBuffers(winObj->window);
        glfwPollEvents();
    }

    return (new RuntimeResult())->success(new Number<double>(0, "", ""));
}

template<>
WindowFunction<int>::WindowFunction(Window<int> *winObj, string name, vector<string> argNames,
                                          map<string, BaseValue *> defaultArgs,
                                          string fName, string fTxt) : BaseFunction<int>(name, argNames, defaultArgs,
                                                                                         fName,
                                                                                         fTxt, CLASS_FUNC) {
    this->winObj = winObj;
    this->defaultArgs = defaultArgs;
    type = TOK_TYPE::T_FUNC;

    funcMap["execute_start"] = &WindowFunction<int>::execute_start;
}

template<>
WindowFunction<int> *WindowFunction<int>::copy() {
    auto *func = new WindowFunction<int>(winObj, name, argNames, defaultArgs, fName, fTxt);
    func->setContext(ctx);
    func->setPos(posStart, posEnd, line);
    return func;
}

template<>
RuntimeResult *WindowFunction<int>::execute(vector<BaseValue *> args) {
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
string WindowFunction<int>::toString() {
    return "<WindowFunction: " + name + ">";
}