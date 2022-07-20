//
// Created by Preeti Thorat on 7/9/22.
//

#include "Text.h"
#include "TextFunction.h"

template <>
Text<int>::Text(Number<double> *X, Number<double> *Y, Number<double> *width, Number<double> *height,
                String<string> *text) : Widget<int>() {
    this->X = X;
    this->Y = Y;
    this->width = width;
    this->height = height;
    this->text = text;
    display = new Fl_Text_Display(X->getValue(), Y->getValue(), width->getValue(), height->getValue());
    display->box(FL_NO_BOX);
    display->buffer(&buffer);
    buffer.text(text->getValue().c_str());

    //Implement setText function
    map<string, BaseValue *> defaultArgs;
    symbolTable->set("setText", new TextFunction<int>(this, "setText", {"text"},
                                                               defaultArgs, "",
                                                               ""));

    widget = display;
}

template <>
BaseValue *Text<int>::copy() {
    return new Text<int>(X, Y, width, height, text);
}

template <>
string Text<int>::toString() {
    return "<Text>";
}