//
// Created by Preeti Thorat on 2/3/22.
//

#include "UsableClass.h"
#include <utility>

template<>
UsableClass<int>::UsableClass(string f, string txt, string className, vector<ClassFunction<int> *> methods, Context * context) : Value<int>(0, T_CLASS, std::move(f), std::move(txt)) {
    map<string, BaseValue *> defaultArgs;
    this->className = std::move(className);
    ctx = context;

    for (auto &method : methods) {
        ctx->symbolTable->set(method->name, new ClassFunction<int>(method->fName, method->fTxt, method->name, method->body, method->argNames, method->defaultArgs, method->lines, method->autoReturn, ctx, method->className));
    }
}

template<>
BaseValue *UsableClass<int>::getFromSymbolTable(string key) {
    BaseValue * v = ctx->symbolTable->get(key);
    return v;
}

template<>
BaseValue * UsableClass<int>::copy() {
    return new UsableClass<int>(*this);
}

template<>
string UsableClass<int>::toString() {
    return "<InstantiatedClass: " + className + ">";
}