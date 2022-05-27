//
// Created by Preeti Thorat on 3/21/22.
//

#include "Json.h"
#include "JsonFunction.h"

template<>
Json<int>::Json() : Value<int>(0, TOK_TYPE::T_CLASS, "", "") {
    map<string, BaseValue *> defaultArgs;

    symbolTable->set("loads", new JsonFunction<int>("loads", {"string"}, defaultArgs, "", ""));
    symbolTable->set("dumps", new JsonFunction<int>("dumps", {"value"}, defaultArgs, "", ""));
    symbolTable->set("NULL", new String<string>(jsonNull, "", ""));
}

template<>
BaseValue * Json<int>::copy() {
    return new Json<int>();
}

template<>
string Json<int>::toString() {
    return "<Module: json>";
}