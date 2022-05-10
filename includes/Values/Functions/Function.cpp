//
// Created by Preeti Thorat on 12/9/21.
//

#include "Function.h"

#include "../../Interpreter/Interpreter.h"

template<>
Function<int>::Function(string fName, string fTxt, string name, Node *body, vector<string> argNames, map<string, BaseValue *> defaultArgs,
                        vector<string> uses, vector<string> lines, bool autoReturn) : BaseFunction<int>(name, argNames, defaultArgs, fName, fTxt, NORMAL_FUNC) {
    this->autoReturn = autoReturn;
    this->lines = lines;
    this->body = body;
    this->uses = uses;
}

template<>
RuntimeResult *Function<int>::execute(vector<BaseValue *> args) {
    auto *res = new RuntimeResult();
    auto *interpreter = new Interpreter(fName, lines);

    Context *execCtx = generateNewContext();

    res->reg(checkAndPopulateArgs(args, argNames, execCtx));
    if (res->shouldReturn()) return res;

    BaseValue *value = res->reg(interpreter->visit(body, execCtx));
    if (res->shouldReturn() && res->funcReturnValue == nullptr) {
        return res;
    }
    // If auto returning with a oneliner, return the value
    BaseValue * retVal = (autoReturn ? value : nullptr);
    if(retVal == nullptr) {
        // Look for a return statement, otherwise return null
        retVal = res->funcReturnValue ? res->funcReturnValue : new Number<double>(0, "", "");
    }

    for (auto &use : uses) {
        BaseValue *val = execCtx->symbolTable->get(use);
        if (!val) {
            // Add warn that the use is not used
            continue;
        }
        execCtx->symbolTable->parent->set(use, val);
    }

    return res->success(retVal);
}

template<>
Function<int> *Function<int>::copy() {
    Function<int> *func = new Function<int>(fName, fTxt, name, body, argNames, defaultArgs, uses, lines, autoReturn);
    func->setContext(ctx);
    func->setPos(posStart, posEnd, line);
    return func;
}

template<>
string Function<int>::toString() {
    return "{Func: " + name + "}";
}