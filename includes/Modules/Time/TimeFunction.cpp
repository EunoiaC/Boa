//
// Created by Preeti Thorat on 4/16/22.
//

#include "TimeFunction.h"
#include <thread>
#include <chrono>

template<>
RuntimeResult *TimeFunction<int>::execute_waitMs(Context *execCtx) {
    auto * res = new RuntimeResult();
    BaseValue *temp = execCtx->symbolTable->get("time");
    if(temp->type != TOK_TYPE::T_NUM){
        return (new RuntimeResult())->failure(new RuntimeError(
                temp->posStart,
                temp->posEnd,
                temp->line,
                temp->fName,
                temp->fTxt,
                "Expected a NUMBER",
                execCtx
        ));
    }
    long time = dynamic_cast<Number<double> *>(temp)->getValue();

    this_thread::sleep_for(chrono::milliseconds(time));

    return res->success(new Number<double>(0, "", ""));
}

template<>
RuntimeResult *TimeFunction<int>::execute_waitSec(Context *execCtx) {
    auto * res = new RuntimeResult();
    BaseValue *temp = execCtx->symbolTable->get("time");
    if(temp->type != TOK_TYPE::T_NUM){
        return (new RuntimeResult())->failure(new RuntimeError(
                temp->posStart,
                temp->posEnd,
                temp->line,
                temp->fName,
                temp->fTxt,
                "Expected a NUMBER",
                execCtx
        ));
    }
    long time = dynamic_cast<Number<double> *>(temp)->getValue();

    this_thread::sleep_for(chrono::seconds(time));

    return res->success(new Number<double>(0, "", ""));
}

template<>
RuntimeResult *TimeFunction<int>::execute_currTime(Context *execCtx) {
    return (new RuntimeResult())->success(new TimeValue<int>(time(0)));
}

template<>
TimeFunction<int>::TimeFunction(string name, vector<string> argNames, map<string, BaseValue *> defaultArgs,
                                    string fName, string fTxt) : BaseFunction<int>(name, argNames, defaultArgs, fName,
                                                                                   fTxt, CLASS_FUNC) {
    type = TOK_TYPE::T_FUNC;
    funcMap["execute_sleepMs"] = &TimeFunction<int>::execute_waitMs;
    funcMap["execute_sleepSec"] = &TimeFunction<int>::execute_waitSec;
    funcMap["execute_currTime"] = &TimeFunction<int>::execute_currTime;
}

template<>
RuntimeResult *TimeFunction<int>::execute(vector<BaseValue *> args) {
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
TimeFunction<int> *TimeFunction<int>::copy() {
    auto *func = new TimeFunction<int>(name, argNames, defaultArgs, fName, fTxt);
    func->setContext(ctx);
    func->setPos(posStart, posEnd, line);
    return func;
}

template<>
string TimeFunction<int>::toString() {
    return "<TimeFunction: " + name + ">";
}