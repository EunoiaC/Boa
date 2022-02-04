//
// Created by Preeti Thorat on 2/3/22.
//

#include "Class.h"

#include <utility>


template<> Class<int>::Class(Context *context, string name, string fName, string fTxt, vector<string> constructorArgs,
                             vector<Function<int> *> methods) : Value<int>(-1, T_CLASS, std::move(fName), std::move(fTxt)){
    this->classContext = context;
    this->methods = std::move(methods);
    this->name = std::move(name);
    this->constructorArgs = std::move(constructorArgs);
}