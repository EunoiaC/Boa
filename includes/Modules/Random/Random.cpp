//
// Created by Preeti Thorat on 1/28/22.
//

#include "Random.h"

#include <utility>
#include "RandomFunction.h"

template<>
Random<int>::Random(string f, string txt) : Value<int>(0, "RANDOM", std::move(f), std::move(txt)) {
    map<string, BaseValue *> defaultArgs;

    symbolTable->set("randrange", new RandomFunction<int>("randrange", {"min", "max"}, defaultArgs, "", ""));
    symbolTable->set("choose", new RandomFunction<int>("choose", {"value"}, defaultArgs, "", ""));
    symbolTable->set("shuffle", new RandomFunction<int>("shuffle", {"value"}, defaultArgs, "", ""));
}

template<>
BaseValue * Random<int>::copy() {
    return new Random<int>(*this);
}

template<>
string Random<int>::toString() {
    return "<Module: random>";
}