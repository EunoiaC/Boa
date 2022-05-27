//
// Created by Preeti Thorat on 4/16/22.
//

#include "Time.h"
#include "TimeFunction.h"

template<>
Time<int>::Time() : Value<int>(0, TOK_TYPE::T_CLASS, "", "") {
    map<string, BaseValue *> defaultArgs;

    symbolTable->set("sleepMs", new TimeFunction<int>("sleepMs", {"time"}, defaultArgs, "", ""));
    symbolTable->set("sleepSec", new TimeFunction<int>("sleepSec", {"time"}, defaultArgs, "", ""));
}

template<>
BaseValue * Time<int>::copy() {
    return new Time<int>();
}

template<>
string Time<int>::toString() {
    return "<Module: time>";
}