//
// Created by Preeti Thorat on 1/18/22.
//

#include "ListFunction.h"

template <>
RuntimeResult *ListFunction<int>::execute_slice(Context *execCtx) {
    auto *res = new RuntimeResult();

    //END INDEX IS NON INCLUSIVE

    BaseValue * start = execCtx->symbolTable->get("startIdx");
    BaseValue * end = execCtx->symbolTable->get("endIdx");

    vector<BaseValue *> toSlice = value->copy()->getValue();

    if(start->type != T_NUM){
        return res->failure(new RuntimeError(
                start->posStart,
                start->posEnd,
                start->line,
                start->fName,
                start->fTxt,
                "Expected a number",
                execCtx
        ));
    }

    if(end->type != T_NUM) {
        return res->failure(new RuntimeError(
                end->posStart,
                end->posEnd,
                end->line,
                start->fName,
                start->fTxt,
                "Expected a number",
                execCtx
        ));
    }

    int startIndex = ((Number<double>*)start)->getValue();
    int endIndex = ((Number<double>*)end)->getValue();

    if(startIndex < 0 || startIndex >= toSlice.size()){
        return res->failure(new RuntimeError(
                start->posStart,
                start->posEnd,
                start->line,
                start->fName,
                start->fTxt,
                "Start index out of range",
                execCtx
        ));
    }

    if((endIndex < 0 || endIndex >= toSlice.size()) && endIndex != -1){
        return res->failure(new RuntimeError(
                end->posStart,
                end->posEnd,
                end->line,
                end->fName,
                end->fTxt,
                "End index out of range",
                execCtx
        ));
    }

    if(endIndex == -1) {
        endIndex = toSlice.size();
    }

    return res->success(new List<vector<BaseValue *>>(vector<BaseValue *>(toSlice.begin() + startIndex, toSlice.begin() + endIndex), "", ""));
}

template <>
RuntimeResult *ListFunction<int>::execute_pop(Context *execCtx) {
    auto *res = new RuntimeResult();

    BaseValue *index = execCtx->symbolTable->get("index");
    if(index->type != T_NUM) {
        return res->failure(new RuntimeError(
                index->posStart,
                index->posEnd,
                index->line,
                index->fName,
                index->fTxt,
                "Expected a NUMBER",
                execCtx
        ));
    }

    int idx = ((Number<double>*) index)->getValue();

    if(idx < 0 || idx >= value->elements.size()){
        return res->failure(new RuntimeError(
                index->posStart,
                index->posEnd,
                index->line,
                index->fName,
                index->fTxt,
                "Index out of range",
                execCtx
        ));
    }

    value->elements.erase(value->elements.begin() + idx);
    return res->success(value);
}

template <>
RuntimeResult *ListFunction<int>::execute_append(Context *execCtx) {
    auto *res = new RuntimeResult();

    value->elements.push_back(execCtx->symbolTable->get("value"));
    return res->success(value);
}

template<>
ListFunction<int>::ListFunction(List<vector<BaseValue *>>* value, string name, vector<string> argNames, map<string, BaseValue *> defaultArgs, string fName, string fTxt)
        : BaseFunction<int>(name, argNames, defaultArgs, fName, fTxt) {
    type = "FUNCTION"; // It doesnt work w/out this idk why
    this->value = value;
    funcMap["execute_pop"] = &ListFunction<int>::execute_pop;
    funcMap["execute_append"] = &ListFunction<int>::execute_append;
    funcMap["execute_slice"] = &ListFunction<int>::execute_slice;
    this->defaultArgs = defaultArgs;
}

template<>
RuntimeResult *ListFunction<int>::execute(vector<BaseValue *> args) {
    RuntimeResult *res = new RuntimeResult();
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
ListFunction<int> *ListFunction<int>::copy() {
    auto *func = new ListFunction<int>(value, name, argNames, defaultArgs, fName, fTxt);
    func->setContext(ctx);
    func->setPos(posStart, posEnd, line);
    return func;
}

template<>
string ListFunction<int>::toString() {
    return "<StringFunction: " + name + ">";
}