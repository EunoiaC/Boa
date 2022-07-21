//
// Created by Preeti Thorat on 7/18/22.
//

#include "Widget.h"
#include "WidgetFunction.h"

template <>
Widget<int>::Widget() : Value<int>(0, TOK_TYPE::CLASS, "f", "txt") {

    map <string, BaseValue *> defaultArgs;
    symbolTable->set("color", new WidgetFunction<int>(this, "color", {"color"}, defaultArgs, "", ""));
    symbolTable->set("box", new WidgetFunction<int>(this, "box", {"box"}, defaultArgs, "", ""));
    symbolTable->set("setCallback", new WidgetFunction<int>(this, "setCallback", {"callback"},
                                                               defaultArgs, "",
                                                               ""));
    symbolTable->set("hide", new WidgetFunction<int>(this, "hide", {}, defaultArgs, "", ""));
    symbolTable->set("show", new WidgetFunction<int>(this, "show", {}, defaultArgs, "", ""));
    symbolTable->set("redraw", new WidgetFunction<int>(this, "redraw", {}, defaultArgs, "", ""));
    symbolTable->set("getValue", new WidgetFunction<int>(this, "getValue", {}, defaultArgs, "", ""));
    symbolTable->set("labelColor", new WidgetFunction<int>(this, "labelColor", {"color"}, defaultArgs, "", ""));
}

template <>
BaseValue *Widget<int>::copy() {
    Widget<int> * w = new Widget<int>();
    w->widget = widget;
    return w;
}

template <>
string Widget<int>::widgetVal() {
    return "";
}

template <>
string Widget<int>::toString() {
    return "<Widget>";
}