//
// Created by Preeti Thorat on 4/9/22.
//

#include "MapFunction.h"
#include <ranges>

template<typename A, typename B>
pair<B,A> flip_pair(const pair<A,B> &p)
{
    return pair<B,A>(p.second, p.first);
}

template<typename A, typename B>
multimap<B,A> flip_map(const map<A,B> &src) {
    multimap<B, A> dst;
    transform(src.begin(), src.end(), inserter(dst, dst.begin()),
                   flip_pair<A, B>);
    return dst;
}

template<>
RuntimeResult *MapFunction<int>::execute_sortByValue(Context *execCtx) {
    auto * res = new RuntimeResult();
    multimap<BaseValue *, BaseValue *> dst = flip_map(value->getValue());

    map<BaseValue *, BaseValue *> m;

    for(auto it = dst.begin(), end = dst.end(); it != end; ++it)
    {
        m[it->first] = it->second;
    }

    auto *nMap = new Map<map<BaseValue *, BaseValue *>>(m, "", "");
    return res->success(nMap);
}

template<>
RuntimeResult *MapFunction<int>::execute_getKeys(Context *execCtx) {
    auto * res = new RuntimeResult();

    vector<BaseValue *> keys;

    transform(
            value->dict.begin(),
            value->dict.end(),
            std::back_inserter(keys),
            [](const auto &pair){return pair.first;});
    return res->success(new List<vector<BaseValue*>>(keys, "", ""));
}

template<>
MapFunction<int>::MapFunction(Map<map<BaseValue *, BaseValue *>>* value, string name, vector<string> argNames, map<string, BaseValue *> defaultArgs, string fName, string fTxt)
        : BaseFunction<int>(name, argNames, defaultArgs, fName, fTxt, CLASS_FUNC) {
    type = TOK_TYPE::T_FUNC; // It doesnt work w/out this idk why
    this->value = value;
    funcMap["execute_sortByValue"] = &MapFunction<int>::execute_sortByValue;
    funcMap["execute_getKeys"] = &MapFunction<int>::execute_getKeys;
    this->defaultArgs = defaultArgs;
}

template<>
RuntimeResult *MapFunction<int>::execute(vector<BaseValue *> args, map<string, BaseValue *> kwargs) {
    RuntimeResult *res = new RuntimeResult();
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
MapFunction<int> *MapFunction<int>::copy() {
    auto *func = new MapFunction<int>(value, name, argNames, defaultArgs, fName, fTxt);
    func->setContext(ctx);
    func->setPos(posStart, posEnd, line);
    return func;
}

template<>
string MapFunction<int>::toString() {
    return "<MapFunction: " + name + ">";
}