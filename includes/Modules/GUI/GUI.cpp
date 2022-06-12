//
// Created by Preeti Thorat on 5/30/22.
//

#include "GUI.h"

template<>
GUI<int>::GUI() : Value<int>(0, TOK_TYPE::CLASS, "f", "txt") {
    map<string, BaseValue *> defaultArgs;
}

template<>
BaseValue * GUI<int>::copy() {
    return new GUI<int>();
}

template<>
string GUI<int>::toString() {
    return "<Module: GUI>";
}

