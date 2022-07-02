//
// Created by Preeti Thorat on 7/2/22.
//

#include "SQLite3.h"
#include "SQLite3Function.h"

template<>
SQLite3<int>::SQLite3() : Value<int>(0, TOK_TYPE::T_CLASS, "", "") {
    map<string, BaseValue *> defaultArgs;

    symbolTable->set("open", new SQLite3Function<int>("open", {"db"}, defaultArgs, "", ""));
}

template<>
BaseValue *SQLite3<int>::copy() {
    return new SQLite3<int>();
}

template<>
string SQLite3<int>::toString() {
    return "<Module: SQLite3>";
}