//
// Created by Preeti Thorat on 7/10/22.
//

#include "TextInput.h"
#include "TextInputFunction.h"

template <>
TextInput<int>::TextInput(Number<double> *X, Number<double> *Y, Number<double> *width, Number<double> *height,
                String<string> *text) : Widget<int>() {
    this->X = X;
    this->Y = Y;
    this->width = width;
    this->height = height;
    this->text = text;
    input = new Fl_Input(X->getValue(), Y->getValue(), width->getValue(), height->getValue());
    input->value(text->val.c_str());

    map<string, BaseValue *> defaultArgs;

    widget = input;
}

template <>
BaseValue *TextInput<int>::copy() {
    return new TextInput<int>(X, Y, width, height, text);
}

template <>
string TextInput<int>::widgetVal() {
    return input->value();
}

template <>
string TextInput<int>::toString() {
    return "<Text>";
}