//
// Created by Preeti Thorat on 2/3/22.
//

#include "Class.h"

#include <utility>


template<>
Class<int>::Class(Context *context, string name, string fName, string fTxt, vector<Token<string> *> constructorArgs,
                  map<string, BaseValue *> defaultArgs,
                  vector<ClassFunction<int> *> methods) : Value<int>(-1, T_CLASS, std::move(fName), std::move(fTxt)) {
    classContext = context;
    symbolTable = classContext->symbolTable;
    this->methods = std::move(methods);
    this->name = std::move(name);
    this->constructorArgs = std::move(constructorArgs);
    this->defaultArgs = std::move(defaultArgs);
}


template<>
BaseValue *Class<int>::copy() {
    auto * copy = new Class<int>(classContext, name, fName, fTxt, constructorArgs, defaultArgs, methods);
    copy->setPos(posStart, posEnd, line);
    copy->setContext(classContext);
    return copy;
}

template<>
RuntimeResult *Class<int>::execute(vector<BaseValue *> args) {
    return (new RuntimeResult())->success(new Number<double>(-1, "", ""));
}

template<>
string Class<int>::toString() {
    return "<Class: " + name + ">";
}