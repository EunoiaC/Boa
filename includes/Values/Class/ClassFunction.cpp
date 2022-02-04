//
// Created by Preeti Thorat on 2/3/22.
//

#include "ClassFunction.h"

#include <utility>

#include "../../Interpreter/Interpreter.h"

template<>
ClassFunction<int>::ClassFunction(string fName, string fTxt, string name, Node *body, vector<string> argNames, map<string, BaseValue *> defaultArgs,
                                  vector<string> lines, bool autoReturn, Context * ctx) : BaseFunction<int>(std::move(name), std::move(argNames), std::move(defaultArgs), std::move(fName), std::move(fTxt)) {
    this->autoReturn = autoReturn;
    this->lines = lines;
    this->body = body;
    this->classCtx = ctx;
}

template<>
RuntimeResult *ClassFunction<int>::execute(vector<BaseValue *> args) {
    auto *res = new RuntimeResult();
    auto *interpreter = new Interpreter(fName, lines);

    res->reg(checkAndPopulateArgs(args, argNames, classCtx));
    if (res->shouldReturn()) return res;

    BaseValue *value = res->reg(interpreter->visit(body, classCtx));
    if (res->shouldReturn() && res->funcReturnValue == nullptr) {
        return res;
    }
    // If auto returning with a oneliner, return the value
    BaseValue * retVal = (autoReturn ? value : nullptr);
    if(retVal == nullptr) {
        // Look for a return statement, otherwise return null
        retVal = res->funcReturnValue ? res->funcReturnValue : new Number<double>(0, "", "");
    }
    return res->success(retVal);
}

template<>
ClassFunction<int> *ClassFunction<int>::copy() {
    ClassFunction<int> *func = new ClassFunction<int>(fName, fTxt, name, body, argNames, defaultArgs, lines, autoReturn, ctx);
    func->setContext(ctx);
    func->setPos(posStart, posEnd, line);
    return func;
}

template<>
string ClassFunction<int>::toString() {
    return "<Func: " + name + "> defined in class " + name;
}