//
// Created by Preeti Thorat on 2/3/22.
//

#include "ClassFunction.h"

#include <utility>

#include "../../Interpreter/Interpreter.h"

/* TODO: Make an execCtx with the parentCtx and symboltable the class ctx.
 * Check if the funcName is init(), if so execute that in the classCtx, if the funcName is not init(),
 * then execute the funcName in the execCtx
*/

template<>
string ClassFunction<int>::toString() {
    return "<Func: " + name + "> defined in class " + className;
}

template<>
ClassFunction<int>::ClassFunction(string fName, string fTxt, string name, Node *body, vector<string> argNames, map<string, BaseValue *> defaultArgs,
                                  vector<string> lines, bool autoReturn, Context * context, string className) : BaseFunction<int>(name, argNames, defaultArgs, fName, fTxt, CLASS_FUNC) {
    this->autoReturn = autoReturn;
    this->lines = lines;
    this->body = body;
    this->classCtx = new Context(*context);
    this->ctx = classCtx;
    this->className = className;
}

template<>
RuntimeResult *ClassFunction<int>::execute(vector<BaseValue *> args, map<string, BaseValue *> kwargs) {
    auto *res = new RuntimeResult();
    auto *interpreter = new Interpreter(fName, lines);

    // TODO: Fix kwargs
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
        classCtx->symbolTable->set(it.first, it.second);
    }

    BaseValue *value;
    if (name == "init") {
        res->reg(checkAndPopulateArgs(args, kwargs, argNames, classCtx));
        if (res->shouldReturn()) return res;

        value = res->reg(interpreter->visit(body, classCtx));
        if (res->shouldReturn() && res->funcReturnValue == nullptr) {
            return res;
        }
    } else {
        Context *execCtx = generateNewContext();
        res->reg(checkAndPopulateArgs(args, kwargs, argNames, execCtx));
        if (res->shouldReturn()) return res;

        value = res->reg(interpreter->visit(body, execCtx));
        if (res->shouldReturn() && res->funcReturnValue == nullptr) {
            return res;
        }
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
BaseValue * ClassFunction<int>::setContext(Context *context) {
    return this;
}

template<>
ClassFunction<int> *ClassFunction<int>::copy() {
    ClassFunction<int> *func = new ClassFunction<int>(fName, fTxt, name, body, argNames, defaultArgs, lines, autoReturn, classCtx, className);
    func->setPos(posStart, posEnd, line);
    return func;
}