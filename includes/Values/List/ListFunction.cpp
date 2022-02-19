//
// Created by Preeti Thorat on 1/18/22.
//

#include "ListFunction.h"
#include <algorithm>

template <>
RuntimeResult *ListFunction<int>::execute_slice(Context *execCtx) {
    auto *res = new RuntimeResult();

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

    if(endIndex == -1){
        endIndex = toSlice.size();
    } else {
        endIndex = endIndex + 1;
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

    BaseValue * pos = execCtx->symbolTable->get("pos");

    if(pos->type != T_NUM) {
        return res->failure(new RuntimeError(
                pos->posStart,
                pos->posEnd,
                pos->line,
                pos->fName,
                pos->fTxt,
                "Expected a NUMBER",
                execCtx
        ));
    }

    int posIdx = ((Number<double>*) pos)->getValue();
    if((posIdx < 0 || posIdx >= value->elements.size()) && posIdx != -1){
        return res->failure(new RuntimeError(
                pos->posStart,
                pos->posEnd,
                pos->line,
                pos->fName,
                pos->fTxt,
                "Index out of range",
                execCtx
        ));
    }

    if(posIdx == -1){
        value->elements.push_back(execCtx->symbolTable->get("value"));
    } else {
        value->elements.insert(value->elements.begin() + posIdx, execCtx->symbolTable->get("value"));
    }

    return res->success(value);
}

struct compare
{
    BaseValue* key;
    explicit compare(BaseValue* const &i): key(i) {}

    bool operator()(BaseValue* const &i) {
        return (((Number<double>* ) i->compEquals(key))->getValue() == 1);
    }
};

template<>
RuntimeResult *ListFunction<int>::execute_indexOf(Context *execCtx) {
    BaseValue * key = execCtx->symbolTable->get("key");
    auto itr = find_if(value->elements.begin(), value->elements.end(), compare(key));
    return (new RuntimeResult())->success(
            new Number<double>(itr != value->elements.end() ? distance(value->elements.begin(), itr) : -1, "", ""));
}

template<>
RuntimeResult *ListFunction<int>::execute_set(Context *execCtx) {
    BaseValue * idx = execCtx->symbolTable->get("idx");
    BaseValue * val = execCtx->symbolTable->get("val");
    if(idx->type != T_NUM){
        return (new RuntimeResult())->failure(new RuntimeError(
                idx->posStart,
                idx->posEnd,
                idx->line,
                idx->fName,
                idx->fTxt,
                "Expected a NUMBER",
                execCtx
        ));
    }

    int idxVal = ((Number<double>*) idx)->getValue();
    if(idxVal < 0 || idxVal >= value->elements.size()){
        return (new RuntimeResult())->failure(new RuntimeError(
                idx->posStart,
                idx->posEnd,
                idx->line,
                idx->fName,
                idx->fTxt,
                "Index out of range",
                execCtx
        ));
    }

    value->elements[idxVal] = val;
    return (new RuntimeResult())->success(value);
}

template<>
RuntimeResult *ListFunction<int>::execute_sort(Context *execCtx) {
    auto *copy = value->copy();
    RuntimeResult *res = new RuntimeResult();
    Error * error = nullptr;

    BaseValue * compareFunc = execCtx->symbolTable->get("func");
    if(compareFunc->type != T_FUNC){
        return res->failure(new RuntimeError(
                compareFunc->posStart,
                compareFunc->posEnd,
                compareFunc->line,
                compareFunc->fName,
                compareFunc->fTxt,
                "Expected a FUNCTION",
                execCtx
        ));
    }

    BaseFunction<int> * func = (BaseFunction<int>*) compareFunc;
    if(func->argNames.size() != 2 && func->getValue() != -10){
        return res->failure(new RuntimeError(
                compareFunc->posStart,
                compareFunc->posEnd,
                compareFunc->line,
                compareFunc->fName,
                compareFunc->fTxt,
                "Expected a function with 2 parameters",
                execCtx
        ));
    }

    sort(copy->elements.begin(), copy->elements.end(), [&](BaseValue* const &a, BaseValue* const &b) {
        Number<double> * val;
        if (func->getValue() != -10){
            RuntimeResult * r = func->execute({a, b});
            if (r->error) {
                error = r->error;
                return false;
            }
            BaseValue * tmp = r->value;
            if (tmp->type != T_NUM){
                error = new RuntimeError(
                        func->posStart,
                        func->posEnd,
                        func->line,
                        func->fName,
                        func->fTxt,
                        "Expected return value of type NUMBER",
                        execCtx
                );
            }
            val = (Number<double>*) tmp;
        } else {
            val = (Number<double>*) a->compSort(b);
        }
        if (a->type == T_NUM) {
            if (((Number<double> *) a)->rtError) {
                error = ((Number<double> *) a)->rtError;
                return false;
            }
        } else if (a->type == T_STRING) {
            if (((String<string> *) a)->rtError) {
                error = ((String<string> *) a)->rtError;
                return false;
            }
        } else if (a->type == T_FUNC) {
            if (((BaseFunction<int> *) a)->rtError) {
                error = ((BaseFunction<int> *) a)->rtError;
                return false;
            }
        } else if (a->type == T_LIST) {
            if (((List<vector<BaseValue *>> *) a)->rtError) {
                error = ((List<vector<BaseValue *>> *) left)->rtError;
                return false;
            }
        } else if (a->type == T_MAP) {
            if (((Map<map<BaseValue *, BaseValue *>> *) a)->rtError) {
                error = ((Map<map<BaseValue *, BaseValue *>> *) a)->rtError;
                return false;
            }
        } else if (a->type == T_CLASS) {
            if (((UsableClass<int> *) a)->rtError) {
                error = ((UsableClass<int> *) a)->rtError;
                return false;
            }
        }
        return (val)->getValue() == 1;
    });
    if (error) return res->failure(error);
    return res->success(copy);
}

template<>
ListFunction<int>::ListFunction(List<vector<BaseValue *>>* value, string name, vector<string> argNames, map<string, BaseValue *> defaultArgs, string fName, string fTxt)
        : BaseFunction<int>(name, argNames, defaultArgs, fName, fTxt, CLASS_FUNC) {
    type = "FUNCTION"; // It doesnt work w/out this idk why
    this->value = value;
    funcMap["execute_pop"] = &ListFunction<int>::execute_pop;
    funcMap["execute_append"] = &ListFunction<int>::execute_append;
    funcMap["execute_slice"] = &ListFunction<int>::execute_slice;
    funcMap["execute_indexOf"] = &ListFunction<int>::execute_indexOf;
    funcMap["execute_set"] = &ListFunction<int>::execute_set;
    funcMap["execute_sort"] = &ListFunction<int>::execute_sort;
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
    return "<ListFunction: " + name + ">";
}