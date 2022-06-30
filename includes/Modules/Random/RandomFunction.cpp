//
// Created by Preeti Thorat on 1/28/22.
//

#include "RandomFunction.h"

template<>
RuntimeResult *RandomFunction<int>::execute_randrange(Context *execCtx) {
    BaseValue * min = execCtx->symbolTable->get("min");
    BaseValue * max = execCtx->symbolTable->get("max");
    if(min->type != TOK_TYPE::T_NUM){
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

    if(max->type != TOK_TYPE::T_NUM){
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
    if(toChoose->type != TOK_TYPE::T_LIST){
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
RuntimeResult *RandomFunction<int>::execute_shuffle(Context *execCtx) {
    BaseValue * toShuffle = execCtx->symbolTable->get("value");
    if(toShuffle->type != TOK_TYPE::T_LIST){
        return (new RuntimeResult())->failure(new RuntimeError(
                toShuffle->posStart,
                toShuffle->posEnd,
                toShuffle->line,
                toShuffle->fName,
                toShuffle->fTxt,
                "Expected a LIST",
                execCtx
        ));
    }

    List<vector<BaseValue *>> * list = ((List<vector<BaseValue *>> *) toShuffle);
    int size = list->elements.size();
    if(size == 0){
        return (new RuntimeResult())->success(list);
    }
    random_device rd;
    auto rng = default_random_engine { rd() };
    shuffle(begin(list->elements), end(list->elements), rng);

    return (new RuntimeResult())->success(list);
}

template<>
RandomFunction<int>::RandomFunction(string name, vector<string> argNames, map<string, BaseValue *> defaultArgs,
                                    string fName, string fTxt) : BaseFunction<int>(name, argNames, defaultArgs, fName,
                                                                                   fTxt, CLASS_FUNC) {
    type = BaseToken::T_FUNC;
    funcMap["execute_randrange"] = &RandomFunction<int>::execute_randrange;
    funcMap["execute_choose"] = &RandomFunction<int>::execute_choose;
    funcMap["execute_shuffle"] = &RandomFunction<int>::execute_shuffle;
}

template<>
RuntimeResult *RandomFunction<int>::execute(vector<BaseValue *> args, map<string, BaseValue *> kwargs) {
    auto *res = new RuntimeResult();
    Context *execCtx = generateNewContext();

    string methodName = "execute_" + name;

    for (auto &it: kwargs) {
        args.push_back(it.second);
        execCtx->symbolTable->set(it.first, it.second);
    }
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