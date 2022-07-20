//
// Created by Preeti Thorat on 7/19/22.
//

#include "Button.h"

template <>
Button<int>::Button(Number<double> *X, Number<double> *Y, Number<double> *width, Number<double> *height,
                String<string> *text) : Widget<int>() {
    this->X = X;
    this->Y = Y;
    this->width = width;
    this->height = height;
    this->text = text;
    btn = new Fl_Button(X->getValue(), Y->getValue(), width->getValue(), height->getValue(), text->val.c_str());

    widget = btn;
}

template <>
BaseValue *Button<int>::copy() {
    return new Button<int>(X, Y, width, height, text);
}

template <>
string Button<int>::toString() {
    return "<Button>";
}