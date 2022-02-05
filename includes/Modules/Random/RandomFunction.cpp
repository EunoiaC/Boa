//
// Created by Preeti Thorat on 1/28/22.
//

#include "RandomFunction.h"
#include "../../Values/List/List.h"
#include <random>

template<>
RuntimeResult *RandomFunction<int>::execute_randrange(Context *execCtx) {
    BaseValue * min = execCtx->symbolTable->get("min");
    BaseValue * max = execCtx->symbolTable->get("max");
    if(min->type != T_NUM){
        return (new RuntimeResult())->failure(new RuntimeError(
                min->posStart,
                min->posEnd,
                min->line,
                min->fName,
                min->fTxt,
                "Expected a NUMBER",
                execCtx
        ));
    }

    if(max->type != T_NUM){
        return (new RuntimeResult())->failure(new RuntimeError(
                max->posStart,
                max->posEnd,
                max->line,
                max->fName,
                max->fTxt,
                "Expected a NUMBER",
                execCtx
        ));
    }

    int minVal = ((Number<double>*)min)->getValue();
    int maxVal = ((Number<double>*)max)->getValue();

    random_device rd; // obtain a random number from hardware
    mt19937 gen(rd()); // seed the generator
    uniform_int_distribution<> distr(minVal, maxVal); // define the range

    return (new RuntimeResult())->success(new Number<double>(distr(rd), "", ""));
}

template<>
RuntimeResult *RandomFunction<int>::execute_choose(Context *execCtx) {
    BaseValue * toChoose = execCtx->symbolTable->get("value");
    if(toChoose->type != T_LIST){
        return (new RuntimeResult())->failure(new RuntimeError(
                toChoose->posStart,
                toChoose->posEnd,
                toChoose->line,
                toChoose->fName,
                toChoose->fTxt,
                "Expected a LIST",
                execCtx
        ));
    }

    List<vector<BaseValue *>> * list = ((List<vector<BaseValue *>> *) toChoose);
    int size = list->getValue().size();
    if(size == 0){
        return (new RuntimeResult())->failure(new RuntimeError(
                toChoose->posStart,
                toChoose->posEnd,
                toChoose->line,
                toChoose->fName,
                toChoose->fTxt,
                "List is empty",
                execCtx
        ));
    }

    random_device rd; // obtain a random number from hardware
    mt19937 gen(rd()); // seed the generator
    uniform_int_distribution<> distr(0, size - 1); // define the range

    return (new RuntimeResult())->success(list->getValue()[distr(rd)]);
}

template<>
RandomFunction<int>::RandomFunction(string name, vector<string> argNames, map<string, BaseValue *> defaultArgs,
                                    string fName, string fTxt) : BaseFunction<int>(name, argNames, defaultArgs, fName,
                                                                                   fTxt, CLASS_FUNC) {
    type = "FUNCTION";
    funcMap["execute_randrange"] = &RandomFunction<int>::execute_randrange;
    funcMap["execute_choose"] = &RandomFunction<int>::execute_choose;
}

template<>
RuntimeResult *RandomFunction<int>::execute(vector<BaseValue *> args) {
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
RandomFunction<int> *RandomFunction<int>::copy() {
    auto *func = new RandomFunction<int>(name, argNames, defaultArgs, fName, fTxt);
    func->setContext(ctx);
    func->setPos(posStart, posEnd, line);
    return func;
}

template<>
string RandomFunction<int>::toString() {
    return "<RandomFunction: " + name + ">";
}