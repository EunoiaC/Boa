//
// Created by Preeti Thorat on 5/30/22.
//

#include "GUI.h"
#include "GUIFunction.h"

template<>
GUI<int>::GUI() : Value<int>(0, TOK_TYPE::CLASS, "f", "txt") {
    map<string, BaseValue *> defaultArgs;

    defaultArgs["width"] = new Number<double>(640, "", "");
    defaultArgs["height"] = new Number<double>(480, "", "");
    defaultArgs["title"] = new String<string>("Window", "", "");
    symbolTable->set("makeWindow", new GUIFunction<int>("makeWindow", {"width", "height", "title"}, defaultArgs, "", ""));
    defaultArgs.clear();
}

template<>
BaseValue * GUI<int>::copy() {
    return new GUI<int>();
}

template<>
string GUI<int>::toString() {
    return "<Module: GUI>";
}

