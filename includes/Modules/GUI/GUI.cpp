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

    defaultArgs["X"] = new Number<double>(0, "", "");
    defaultArgs["Y"] = new Number<double>(0, "", "");
    symbolTable->set("makeText", new GUIFunction<int>("makeText", {"width", "height", "text", "X", "Y"}, defaultArgs, "", ""));
    defaultArgs.clear();

    defaultArgs["X"] = new Number<double>(0, "", "");
    defaultArgs["Y"] = new Number<double>(0, "", "");
    defaultArgs["text"] = new String<string>("", "", "");
    symbolTable->set("makeTextInput", new GUIFunction<int>("makeTextInput", {"width", "height", "X", "Y", "text"}, defaultArgs, "", ""));
    defaultArgs.clear();

    defaultArgs["X"] = new Number<double>(0, "", "");
    defaultArgs["Y"] = new Number<double>(0, "", "");
    defaultArgs["text"] = new String<string>("", "", "");
    symbolTable->set("makeButton", new GUIFunction<int>("makeButton", {"width", "height", "text", "X", "Y"}, defaultArgs, "", ""));
    defaultArgs.clear();

    // FLTK Colors
    symbolTable->set("BLACK", new Number<double>(FL_BLACK, "", ""));
    symbolTable->set("RED", new Number<double>(FL_RED, "", ""));
    symbolTable->set("GREEN", new Number<double>(FL_GREEN, "", ""));
    symbolTable->set("BLUE", new Number<double>(FL_BLUE, "", ""));
    symbolTable->set("CYAN", new Number<double>(FL_CYAN, "", ""));
    symbolTable->set("MAGENTA", new Number<double>(FL_MAGENTA, "", ""));
    symbolTable->set("YELLOW", new Number<double>(FL_YELLOW, "", ""));
    symbolTable->set("WHITE", new Number<double>(FL_WHITE, "", ""));
    symbolTable->set("DARK_BLUE", new Number<double>(FL_DARK_BLUE, "", ""));
    symbolTable->set("DARK_GREEN", new Number<double>(FL_DARK_GREEN, "", ""));
    symbolTable->set("DARK_CYAN", new Number<double>(FL_DARK_CYAN, "", ""));
    symbolTable->set("DARK_RED", new Number<double>(FL_DARK_RED, "", ""));
    symbolTable->set("DARK_MAGENTA", new Number<double>(FL_DARK_MAGENTA, "", ""));
    symbolTable->set("DARK_YELLOW", new Number<double>(FL_DARK_YELLOW, "", ""));

    // FLTK Box Types
    symbolTable->set("NO_BOX", new Number<double>(FL_NO_BOX, "", ""));
    symbolTable->set("FLAT_BOX", new Number<double>(FL_FLAT_BOX, "", ""));
    symbolTable->set("UP_BOX", new Number<double>(FL_UP_BOX, "", ""));
    symbolTable->set("DOWN_BOX", new Number<double>(FL_DOWN_BOX, "", ""));
    symbolTable->set("UP_FRAME", new Number<double>(FL_UP_FRAME, "", ""));
    symbolTable->set("DOWN_FRAME", new Number<double>(FL_DOWN_FRAME, "", ""));
    symbolTable->set("THIN_UP_BOX", new Number<double>(FL_THIN_UP_BOX, "", ""));
    symbolTable->set("THIN_DOWN_BOX", new Number<double>(FL_THIN_DOWN_BOX, "", ""));
    symbolTable->set("THIN_UP_FRAME", new Number<double>(FL_THIN_UP_FRAME, "", ""));
    symbolTable->set("THIN_DOWN_FRAME", new Number<double>(FL_THIN_DOWN_FRAME, "", ""));
    symbolTable->set("ROUND_UP_BOX", new Number<double>(FL_ROUND_UP_BOX, "", ""));
    symbolTable->set("ROUND_DOWN_BOX", new Number<double>(FL_ROUND_DOWN_BOX, "", ""));
}

template<>
BaseValue * GUI<int>::copy() {
    return new GUI<int>();
}

template<>
string GUI<int>::toString() {
    return "<Module: GUI>";
}

